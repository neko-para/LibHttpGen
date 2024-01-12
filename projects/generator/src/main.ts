import { deinitRegenerator, initRegenerator, loadConfig, loadInterface } from './config'
import { Regenerator } from './regenerator'
import { LHGConfig, LHGInterfaceArgumentInfo } from './types'
import { ExprItem, JsonValue, objectEntryToJson, objectToJson } from './utils'

function declareSchema(regen: Regenerator, type: string, schema: JsonValue) {
  regen.add_raw(`template<>
struct lhg::schema_t<${type}>
{
    static constexpr const char* const schema = ${JSON.stringify(JSON.stringify(schema))};
};
`)
}

function processArguments(cfg: Required<LHGConfig>, args: LHGInterfaceArgumentInfo[]) {
  for (const [idx, arg] of args.entries()) {
    if (arg.type in cfg.callback) {
      arg.special = {
        type: 'callback',
        name: arg.type,
        refer: cfg.callback[arg.type]!
      }
      args[idx + cfg.callback[arg.type]!.pass]!.special = {
        type: 'callback_context',
        refer: cfg.callback[arg.type]!,
        param: arg.name
      }
    } else if (arg.type.endsWith(' *')) {
      const pt = arg.type.slice(0, -2)
      if (pt in cfg.opaque) {
        arg.special = {
          type: 'opaque',
          name: pt,
          refer: cfg.opaque[pt]!
        }
      } else if (cfg.output.includes(pt)) {
        arg.special = {
          type: 'output',
          name: pt
        }
      }
    }
  }
  return args
}

function FS(func: string) {
  return `${func}__ft`
}

function AS(arg: string) {
  return `${arg}__at`
}

async function main() {
  const cfg = await loadConfig()
  const int = await loadInterface()
  const regen = await initRegenerator()

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

  regen.add_raw(
    `// clang-format off

#include "LHGUtils.h"
#define LHG_PROCESS
`
  )
  regen.add_sec('lhg.include', '')
  regen.add_raw('')
  regen.add_sec('lhg.custom.global', '')
  regen.add_raw('')

  for (const type in cfg.callback) {
    const name = cfg.callback[type]!.name
    regen.add_raw(`static lhg::callback_manager<${type}> ${name}__Manager;\n`)
  }

  for (const ic of int.interface) {
    const args = processArguments(cfg, ic.argument)
    regen.add_raw(`struct ${FS(ic.name)} {
${args
  .map(
    (arg, idx) => `    struct ${AS(arg.name)} {
        using type = ${arg.type};
        static constexpr size_t index = ${idx};
        static constexpr const char* const name = ${JSON.stringify(arg.name)};
    };
`
  )
  .join('')}    using arguments_t = ${
      ic.argument.length === 0
        ? 'void'
        : `std::tuple<${ic.argument.map(x => AS(x.name)).join(', ')}>`
    };
    using return_t = ${ic.return};
};
`)
    for (const arg of args) {
      if (arg.special) {
        if (arg.special.type === 'callback') {
          regen.add_raw(`template<>
struct lhg::is_callback<${FS(ic.name)}::${AS(arg.name)}>
{
    static constexpr const bool value = true;
    static constexpr const char* const name = ${JSON.stringify(arg.special.refer.name)};
    static constexpr const size_t context = ${arg.special.refer.self};
    using traits = lhg::func_traits<typename ${FS(ic.name)}::${AS(arg.name)}::type>;
    static decltype(${arg.special.refer.name}__Manager) &manager; 
};
decltype(${arg.special.refer.name}__Manager)& lhg::is_callback<${FS(ic.name)}::${AS(
            arg.name
          )}>::manager = ${arg.special.refer.name}__Manager;
`)
        } else if (arg.special.type === 'callback_context') {
          regen.add_raw(`template<>
struct lhg::is_callback_context<${FS(ic.name)}::${AS(arg.name)}>
{
    static constexpr const bool value = true;
    using callback_arg_tag = ${FS(ic.name)}::${AS(arg.special.param)};
};
`)
        } else if (arg.special.type === 'output') {
          regen.add_raw(`template<>
struct lhg::is_output<${FS(ic.name)}::${AS(arg.name)}>
{
    static constexpr const bool value = true;
};
`)
        }
      }
    }
    regen.add_raw('namespace lhg {')
    regen.add_sec(`lhg.custom.${ic.name}.tag`, '')
    regen.add_raw('}\n')
  }

  for (const type in cfg.opaque) {
    regen.add_raw(`static lhg::opaque_manager<${type} *> ${type}__OpaqueManager;\n`)
    declareSchema(regen, `${type} *`, { type: 'string', title: type })

    regen.add_raw(`template<>
struct lhg::is_opaque<${type} *> {
    static constexpr const bool value = true;
    using type = ${type};
    static constexpr const char* const name = ${JSON.stringify(type)};
    static lhg::opaque_manager<${type} *>& manager;
};
lhg::opaque_manager<${type} *>& lhg::is_opaque<${type} *>::manager = ${type}__OpaqueManager;
`)
    const oc = cfg.opaque[type]!
    for (const f of oc.free ?? []) {
      regen.add_raw(`template<>
struct lhg::is_opaque_free<${type} *, ${FS(f)}> {
    static constexpr const bool value = true;
};
`)
    }
    for (const f of oc['non-alloc'] ?? []) {
      regen.add_raw(`template<>
struct lhg::is_opaque_non_alloc<${type} *, ${FS(f)}> {
    static constexpr const bool value = true;
};
`)
    }
  }

  for (const ic of int.interface) {
    const args = processArguments(cfg, ic.argument)

    regen.add_sec(`lhg.custom.${ic.name}.func`, '')

    regen.add_raw(
      `std::optional<json::object> ${ic.name}_Wrapper(json::object __param, std::string &__error) {`
    )

    regen.add_raw(`    if (!lhg::perform_check<${FS(ic.name)}>(__param, __error)) {
        return std::nullopt;
    }
`)

    regen.add_raw(`    typename lhg::arg_set<${FS(ic.name)}>::temp_type __temp;
    typename lhg::arg_set<${FS(ic.name)}>::call_type __call;
    if (!lhg::perform_input<${FS(ic.name)}>(__temp, __param, __error)) {
        return std::nullopt;
    }
    if (!lhg::perform_input_fix<${FS(ic.name)}>(__call, __temp, __param, __error)) {
        return std::nullopt;
    }
`)

    const outputCache: string[] = []
    for (const arg of args) {
      if (arg.special) {
        if (arg.special.type === 'output') {
          outputCache.push(arg.name)
        }
      }
    }
    if (args.length > 0) {
      if (ic.return === 'void') {
        regen.add_raw(`    std::apply(${ic.name}, __call);`)
      } else {
        regen.add_raw(`    auto __return = std::apply(${ic.name}, __call);`)
      }
    } else {
      if (ic.return === 'void') {
        regen.add_raw(`    ${ic.name}();`)
      } else {
        regen.add_raw(`    auto __return = ${ic.name}();`)
      }
    }
    if (ic.return === 'void') {
      regen.add_sec(`lhg.impl.${ic.name}.return`, '    int __ret = 0;')
    } else {
      regen.add_sec(`lhg.impl.${ic.name}.return`, '    auto __ret = __return;')
    }
    regen.add_raw(`    return lhg::perform_output<${FS(ic.name)}>(__call, __ret);`)
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
      `        { "${ic.name}", { &${ic.name}_Wrapper, &lhg::input_helper<${FS(
        ic.name
      )}>, &lhg::output_helper<${FS(ic.name)}> } },`
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
        using lhg::wrap_oper;
${Object.keys(cfg.callback).map(type => {
  const cc = cfg.callback[type]!
  const name = cc.name
  const m = /(.*?) *\(\*\)\(.*\)$/.exec(type)!
  const rt = m[1]!
  return `            // ${name}
        result["/callback/${name}/add"] = wrap_oper({}, ${objectToJson({
          type: 'object',
          properties: {
            data: { type: 'object', properties: { id: { type: 'string' } } }
          }
        })});
        result["/callback/${name}/{id}/del"] = wrap_oper({}, ${objectToJson({
          type: 'object',
          properties: {
            data: {},
            error: { type: 'string' }
          }
        })});
        result["/callback/${name}/{id}/pull"] = ${objectToJson({
          type: 'object',
          properties: {
            data: {
              type: 'object',
              properties: {
                ids: {
                  type: 'array',
                  items: {
                    type: 'string'
                  }
                }
              }
            }
          }
        })};
        result["/callback/${name}/{id}/{cid}/request"] = wrap_oper({}, ${objectToJson({
          type: 'object',
          properties: {
            data: {
              type: 'object',
              properties: (() => {
                const res: JsonValue = {}
                for (const id of Array.from({ length: cc.all }, (_, k) => k)) {
                  if (id != cc.self) {
                    res[cc.arg_name[id]!] = new ExprItem(
                      `json::parse(lhg::schema_t<decltype(std::get<${id}>(lhg::callback_manager<${type}>::CallbackContext::args_type {}))>::schema).value()`
                    )
                  }
                }
                Array.from({ length: cc.all }, (_, k) => k).filter(x => x != cc.self)
                return res
              })()
            },
            error: {
              type: 'string'
            }
          }
        })});
        result["/callback/${name}/{id}/{cid}/response"] = wrap_oper(${objectToJson(
          rt === 'void'
            ? {}
            : {
                return: new ExprItem('json::parse(lhg::schema_t<${rt}>::schema).value()')
              }
        )}, ${objectToJson({ data: {}, error: { type: 'string' } })});
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
