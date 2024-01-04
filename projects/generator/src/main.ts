import { deinitRegenerator, initRegenerator, loadConfig, loadInterface } from './config'
import { expressionItem, objectEntryToJson, objectToJson } from './utils'

async function main() {
  const cfg = await loadConfig()
  const int = await loadInterface()
  const regen = await initRegenerator()

  regen.add_raw(
    `// clang-format off

#include "Utils.h"
#define LHG_PROCESS
`
  )
  regen.add_sec('lhg.include', '')
  regen.add_raw('')
  regen.add_sec('lhg.custom.global', '')
  regen.add_raw('')

  const callback_ids: Record<string, string> = {}

  for (const type in cfg.callback) {
    const id = cfg.callback[type]!.name
    callback_ids[type] = id
    regen.add_raw(`static lhg::callback_manager<${type}> ${id}__Manager;\n`)
  }

  for (const type in cfg.opaque) {
    regen.add_raw(`static lhg::opaque_manager<${type} *> ${type}__OpaqueManager;\n`)
    regen.add_raw(`template <>
struct lhg::schema_t<${type} *>
{
    static constexpr const char* const schema = "string@${type}";
};
`)
  }

  int.interface = int.interface.filter(x => {
    for (const rule of cfg.remove) {
      if (rule.startsWith('/')) {
        if (new RegExp(rule.slice(1)).exec(x.name)) {
          return false
        }
      } else {
        if (rule === x.name) {
          return false
        }
      }
    }
    return true
  })

  for (const ic of int.interface) {
    regen.add_raw(`json::object ${ic.name}_HelperInput() {
    return json::object {`)

    // callback
    let ctxPos: number | null = null
    for (const [idx, arg] of ic.argument.entries()) {
      if (arg.type in callback_ids) {
        ctxPos = idx + cfg.callback[arg.type]!.pass
      }
    }

    for (const [idx, arg] of ic.argument.entries()) {
      // callback
      if (ctxPos === idx) {
        continue
      } else if (arg.type in callback_ids) {
        regen.add_sec(
          `lhg.helper.${ic.name}.input.${arg.name}`,
          `        ${objectEntryToJson(arg.name, `string@${callback_ids[arg.type]!}`)},`
        )
        continue
      }

      // opacity
      if (arg.type.endsWith(' *') && cfg.opaque[arg.type.slice(0, -2)]) {
        regen.add_sec(
          `lhg.helper.${ic.name}.input.${arg.name}`,
          `        { "${arg.name}", "string@${arg.type.slice(0, -2)}" },`
        )
        continue
      }

      if (arg.type.endsWith(' *') && cfg.output.includes(arg.type.slice(0, -2))) {
        continue
      }

      regen.add_sec(
        `lhg.helper.${ic.name}.input.${arg.name}`,
        `        { "${arg.name}", lhg::schema_t<${arg.type}>::schema },`
      )
    }
    regen.add_raw(`    };
}
`)
  }

  for (const ic of int.interface) {
    regen.add_raw(`json::object ${ic.name}_HelperOutput() {
    return json::object {
        { "data", {`)
    regen.add_sec(
      `lhg.helper.${ic.name}.output.return`,
      `            { "return", lhg::schema_t<${ic.return}>::schema },`
    )
    for (const [idx, arg] of ic.argument.entries()) {
      if (arg.type.endsWith(' *') && cfg.output.includes(arg.type.slice(0, -2))) {
        regen.add_sec(
          `lhg.helper.${ic.name}.output.${arg.name}`,
          `            { "${arg.name}", lhg::schema_t<${arg.type}>::schema },`
        )
        continue
      }
    }
    regen.add_raw(`        }},
        { "error", "string" }
    };
}
`)
  }

  for (const ic of int.interface) {
    regen.add_raw(
      `std::optional<json::object> ${ic.name}_Wrapper(json::object __param, std::string &__error) {`
    )

    // callback
    let cbId: string | null = null
    let cbParam: string | null = null
    let ctxPos: number | null = null
    const outputCache: string[] = []
    for (const [idx, arg] of ic.argument.entries()) {
      if (arg.type in callback_ids) {
        ctxPos = idx + cfg.callback[arg.type]!.pass
      }
    }

    // check
    for (const [idx, arg] of ic.argument.entries()) {
      // callback
      if (ctxPos === idx) {
        regen.add_sec(
          `lhg.impl.${ic.name}.arg.${arg.name}.check`,
          `    if (!lhg::check_var<const char*>(__param["${cbParam}"])) {
        __error = "${cbParam} should be string@${cbId}";
        return std::nullopt;
    }`
        )
        continue
      } else if (arg.type in callback_ids) {
        cbId = callback_ids[arg.type]!
        continue
      }

      // opacity
      if (arg.type.endsWith(' *') && cfg.opaque[arg.type.slice(0, -2)]) {
        regen.add_sec(
          `lhg.impl.${ic.name}.arg.${arg.name}.check`,
          `    if (!lhg::check_var<const char*>(__param["${arg.name}"])) {
        __error = "${arg.name} should be string@${arg.type.slice(0, -2)}";
        return std::nullopt;
    }`
        )
        continue
      }

      if (arg.type.endsWith(' *') && cfg.output.includes(arg.type.slice(0, -2))) {
        continue
      }

      regen.add_sec(
        `lhg.impl.${ic.name}.arg.${arg.name}.check`,
        `    if constexpr (lhg::check_t<${arg.type}>::enable) {
        if (!lhg::check_var<${arg.type}>(__param["${arg.name}"])) {
            __error = "${arg.name} should be ${cfg.check[arg.type] ?? arg.type}";
            return std::nullopt;
        }
    }`
      )
    }

    for (const [idx, arg] of ic.argument.entries()) {
      // callback
      if (ctxPos === idx) {
        regen.add_sec(
          `lhg.impl.${ic.name}.arg.${arg.name}`,
          `    auto ${arg.name}_id = __param["${cbParam}"].as_string();
    auto ${arg.name} = ${cbId}__Manager.find(${arg.name}_id).get();
    if (${arg.name}) {
        __error = "${cbParam} not found in manager";
        return std::nullopt;
    }`
        )
        continue
      } else if (arg.type in callback_ids) {
        const m = /\(\*\)\((.*)\)$/.exec(arg.type)
        cbId = callback_ids[arg.type]!
        cbParam = arg.name
        regen.add_sec(
          `lhg.impl.${ic.name}.arg.${arg.name}`,
          `    auto ${arg.name} = &lhg::callback_implementation<${cfg.callback[arg.type]!.self}, ${
            arg.type
          }, ${m![1]}>;`
        )
        continue
      }

      // opacity
      if (arg.type.endsWith(' *') && cfg.opaque[arg.type.slice(0, -2)]) {
        const type = arg.type.slice(0, -2)
        if ((cfg.opaque[type]!.free ?? []).includes(ic.name)) {
          regen.add_sec(
            `lhg.impl.${ic.name}.arg.${arg.name}`,
            `    auto ${arg.name}_id = __param["${arg.name}"].as_string();
    ${type} *${arg.name} = 0;
    ${type}__OpaqueManager.del(${arg.name}_id, ${arg.name});`
          )
        } else {
          regen.add_sec(
            `lhg.impl.${ic.name}.arg.${arg.name}`,
            `    auto ${arg.name}_id = __param["${arg.name}"].as_string();
    auto ${arg.name} = ${type}__OpaqueManager.get(${arg.name}_id);`
          )
        }
        regen.add_raw(`    if (!${arg.name}) {
        __error = "${arg.name} not found in manager.";
        return std::nullopt;
    }`)
        continue
      }

      if (arg.type.endsWith(' *') && cfg.output.includes(arg.type.slice(0, -2))) {
        const type = arg.type.slice(0, -2)
        regen.add_sec(
          `lhg.impl.${ic.name}.arg.${arg.name}`,
          `    auto ${arg.name} = lhg::output_prepare<${type} *>();`
        )
        outputCache.push(arg.name)
        continue
      }

      regen.add_sec(
        `lhg.impl.${ic.name}.arg.${arg.name}`,
        `    auto ${arg.name}_temp = lhg::from_json<${arg.type}>(__param["${arg.name}"]);
    auto ${arg.name} = lhg::from_json_fix<${arg.type}>(${arg.name}_temp);`
      )
    }
    if (ic.return === 'void') {
      regen.add_raw(`    ${ic.name}(`)
    } else {
      regen.add_raw(`    auto __return = ${ic.name}(`)
    }
    regen.add_raw(ic.argument.map(x => `        ${x.name}`).join(',\n'))
    regen.add_raw('    );')
    if (ic.return === 'void') {
      regen.add_sec(`lhg.impl.${ic.name}.return`, '')
    } else {
      if (ic.return.endsWith(' *') && cfg.opaque[ic.return.slice(0, -2)]) {
        const type = ic.return.slice(0, -2)
        regen.add_sec(
          `lhg.impl.${ic.name}.return`,
          `    auto __ret = ${type}__OpaqueManager.add(__return);`
        )
      } else {
        regen.add_sec(`lhg.impl.${ic.name}.return`, '    auto __ret = __return;')
      }
    }
    const outputDic = outputCache
      .map(name => `{ "${name}", lhg::output_finalize(${name}) }`)
      .join(', ')
    regen.add_sec(
      `lhg.impl.${ic.name}.final`,
      `    return json::object { { "return", ${
        ic.return === 'void' ? 'json::value(json::value::value_type::null)' : 'lhg::to_json(__ret)'
      } }, ${outputDic} };`
    )
    regen.add_raw('}\n')
  }

  regen.add_raw(`bool handle_request(Context& ctx, UrlSegments segs) {
    auto obj = json::parse(ctx.req_.body()).value_or(json::object {}).as_object();\n`)

  for (const type in cfg.callback) {
    const cc = cfg.callback[type]!
    const m = /(.*?) *\(\*\)\(.*\)$/.exec(type)!
    const rt = m[1]!
    regen.add_raw(`    // callback ${cc.name}`)
    regen.add_raw(`    if (lhg::handle_callback("${cc.name}", ${
      cc.name
    }__Manager, ctx, segs, obj, [](const auto& args) {
${Array.from({ length: cc.all }, (_, k) => k)
  .filter(x => x != cc.self)
  .map(id => `        auto v${id} = std::get<${id}>(args);`)
  .join('\n')}
        return json::object {
${Array.from({ length: cc.all }, (_, k) => k)
  .filter(x => x != cc.self)
  .map(id => `            { "${cc.arg_name[id]}", v${id} },`)
  .join('\n')}
        };
    }, [](const auto& ret) {
${
  rt === 'void'
    ? '        return 0;'
    : `        if constexpr (lhg::check_t<${rt}>::enable) {
            if (!lhg::check_var<${rt}>(ret)) {
                return std::nullopt;
            }
        }
        return lhg::from_json<${rt}>(ret);`
}
    })) {
        return true;
    }
`)
  }

  for (const type in cfg.opaque) {
    regen.add_raw(`    // opaque ${type}`)
    regen.add_raw(`    if (lhg::handle_opaque("${type}", ${type}__OpaqueManager, ctx, segs, obj)) {
        return true;
    }
`)
  }

  regen.add_raw(`    const static lhg::api_info_map wrappers = {`)
  for (const ic of int.interface) {
    regen.add_raw(
      `        { "${ic.name}", { &${ic.name}_Wrapper, &${ic.name}_HelperInput, &${ic.name}_HelperOutput } },`
    )
  }
  regen.add_raw(`    };
    if (lhg::handle_api(ctx, segs, obj, wrappers)) {
        return true;
    }
`)

  regen.add_raw(`    if (lhg::handle_help(ctx, segs, wrappers, { ${Object.keys(cfg.opaque)
    .map(x => `"${x}"`)
    .join(', ')} }, [](json::object& result) {
${Object.keys(cfg.callback).map(type => {
  const name = callback_ids[type]!
  const cc = cfg.callback[type]!
  const m = /(.*?) *\(\*\)\(.*\)$/.exec(type)!
  const rt = m[1]!
  return `            // ${name}
            result["/callback/${name}/add"] = ${objectToJson({
              body: {},
              response: { data: { id: 'string' } }
            })};
            result["/callback/${name}/:id/del"] = ${objectToJson({
              body: {},
              response: { data: {}, error: 'string' }
            })};
            result["/callback/${name}/:id/pull"] = ${objectToJson({
              body: {},
              response: { data: { ids: 'string[]' } }
            })};
            result["/callback/${name}/:id/:cid/request"] = { { "body", json::object {} }, { "response", { { "data", json::object {
${Array.from({ length: cc.all }, (_, k) => k)
  .filter(x => x != cc.self)
  .map(
    id =>
      `                { "${cc.arg_name[id]}", lhg::schema_t<decltype(std::get<${id}>(lhg::callback_manager<${type}>::CallbackContext::args_type {}))>::schema },`
  )
  .join('\n')}
            } }, { "error", "string" } } } };
            result["/callback/${name}/:id/:cid/response"] = ${objectToJson({
              body:
                rt === 'void'
                  ? {}
                  : {
                      return: new expressionItem('lhg::schema_t<${rt}>::schema')
                    },
              response: { data: {}, error: 'string' }
            })};
`
})}
    })) {
        return true;
    }
`)

  regen.add_raw('    return false;\n}')

  await deinitRegenerator(regen)
}

main()
