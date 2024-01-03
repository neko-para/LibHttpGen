import fs from 'fs/promises'
import path from 'path'

import { Regenerator } from './regenerator'

interface Config {
  callback: Record<
    string,
    {
      name: string
      pass: number
      self: number
      all: number
      argn: string[]
    }
  >
  opaque: string[]
  opaque_free: Record<string, string[]>
  output: string[]
  remove: string[]
  check: Record<string, string>
}

interface Interface {
  interface: {
    name: string
    return: string
    argument: {
      name: string
      type: string
    }[]
  }[]
}

async function main() {
  const root = '..'
  const source_path = path.join(root, 'wrapper.cpp')
  const config_path = path.join(root, 'config.json')
  const interface_path = path.join(root, 'interface.json')
  const cfg: Config = JSON.parse(await fs.readFile(config_path, 'utf-8'))
  const int: Interface = JSON.parse(await fs.readFile(interface_path, 'utf-8'))

  const regen = new Regenerator({
    end: '// LHG SEC END',
    default: '// LHG SEC DEF',
    parseId: row => {
      const m = /\/\/ LHG SEC BEGIN (\S+)/.exec(row.trim())
      return m ? m[1]! : null
    },
    buildId: id => {
      return `// LHG SEC BEGIN ${id}`
    }
  })

  await regen.load(source_path)

  regen.add_raw(
    `// clang-format off

#include "helper.h"
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
    regen.add_raw(`static callback_manager<${type}> ${id}__Manager;\n`)
  }

  for (const type of cfg.opaque) {
    regen.add_raw(`static HandleManager<${type} *> ${type}__OpaqueManager;\n`)
    regen.add_raw(`template <>
struct schema_t<${type} *>
{
    static constexpr const char* schema = "string@${type}";
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
          `        { "${arg.name}", "string@${callback_ids[arg.type]!}" },`
        )
        continue
      }

      // opacity
      if (arg.type.endsWith(' *') && cfg.opaque.includes(arg.type.slice(0, -2))) {
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
        `        { "${arg.name}", schema_t<${arg.type}>::schema },`
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
      `            { "return", schema_t<${ic.return}>::schema },`
    )
    for (const [idx, arg] of ic.argument.entries()) {
      if (arg.type.endsWith(' *') && cfg.output.includes(arg.type.slice(0, -2))) {
        regen.add_sec(
          `lhg.helper.${ic.name}.output.${arg.name}`,
          `            { "${arg.name}", schema_t<${arg.type}>::schema },`
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
          `    if (!check_var<const char*>(__param["${cbParam}"])) {
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
      if (arg.type.endsWith(' *') && cfg.opaque.includes(arg.type.slice(0, -2))) {
        regen.add_sec(
          `lhg.impl.${ic.name}.arg.${arg.name}.check`,
          `    if (!check_var<const char*>(__param["${arg.name}"])) {
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
        `    if constexpr (check_var_t<${arg.type}>::value) {
        if (!check_var<${arg.type}>(__param["${arg.name}"])) {
            __error = "${arg.name} should be ${cfg.check[arg.type] ?? arg.type}";
            return std::nullopt;
        }
    }`
      )
    }

    cbId = null
    cbParam = null
    ctxPos = null
    for (const [idx, arg] of ic.argument.entries()) {
      // callback
      if (ctxPos === idx) {
        regen.add_sec(
          `lhg.impl.${ic.name}.arg.${arg.name}`,
          `    auto ${arg.name}_id = __param["${cbParam}"].as_string();
    auto ${arg.name} = ${cbId}__Manager.find(${arg.name}_id).get();`
        )
        continue
      } else if (arg.type in callback_ids) {
        const m = /\(\*\)\((.*)\)$/.exec(arg.type)
        cbId = callback_ids[arg.type]!
        cbParam = arg.name
        regen.add_sec(
          `lhg.impl.${ic.name}.arg.${arg.name}`,
          `    auto ${arg.name} = &__CallbackImpl<${cfg.callback[arg.type]!.self}, ${arg.type}, ${
            m![1]
          }>;`
        )
        continue
      }

      // opacity
      if (arg.type.endsWith(' *') && cfg.opaque.includes(arg.type.slice(0, -2))) {
        const type = arg.type.slice(0, -2)
        if ((cfg.opaque_free[type] ?? []).includes(ic.name)) {
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
          `    auto ${arg.name} = output_prepare<${type} *>();`
        )
        outputCache.push(arg.name)
        continue
      }

      regen.add_sec(
        `lhg.impl.${ic.name}.arg.${arg.name}`,
        `    auto ${arg.name}_temp = from_json<${arg.type}>(__param["${arg.name}"]);
    auto ${arg.name} = from_json_fix<${arg.type}>(${arg.name}_temp);`
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
      if (ic.return.endsWith(' *') && cfg.opaque.includes(ic.return.slice(0, -2))) {
        const type = ic.return.slice(0, -2)
        regen.add_sec(
          `lhg.impl.${ic.name}.return`,
          `    auto __ret = ${type}__OpaqueManager.add(__return);`
        )
      } else {
        regen.add_sec(`lhg.impl.${ic.name}.return`, '    auto __ret = __return;')
      }
    }
    const outputDic = outputCache.map(name => `{ "${name}", output_finalize(${name}) }`).join(', ')
    regen.add_sec(
      `lhg.impl.${ic.name}.final`,
      `    return json::object { { "return", ${
        ic.return === 'void' ? 'json::value(json::value::value_type::null)' : 'to_json(__ret)'
      } }, ${outputDic} };`
    )
    regen.add_raw('}\n')
  }

  regen.add_raw(`bool handle_request(Context& ctx, UrlSegments segs) {
    auto obj = json::parse(ctx.req_.body()).value_or(json::object {}).as_object();`)
  for (const type in cfg.callback) {
    const cc = cfg.callback[type]!
    regen.add_raw(`    // callback ${cc.name}`)
    regen.add_raw(`    if (handle_callback("${cc.name}", ${
      cc.name
    }__Manager, ctx, segs, [](const auto& args) {
${Array.from({ length: cc.all }, (_, k) => k)
  .filter(x => x != cc.self)
  .map(id => `        auto v${id} = std::get<${id}>(args);`)
  .join('\n')}
        return json::object {
${Array.from({ length: cc.all }, (_, k) => k)
  .filter(x => x != cc.self)
  .map(id => `            { "${cc.argn[id]}", v${id} },`)
  .join('\n')}
        };
    })) {
        return true;
    }`)
  }
  regen.add_raw(
    `    const static std::map<std::string, std::tuple<
        std::optional<json::object> (*)(json::object, std::string&),
        json::object (*)(),
        json::object (*)()
    >> wrappers = {`
  )
  for (const ic of int.interface) {
    regen.add_raw(
      `        { "${ic.name}", std::make_tuple(&${ic.name}_Wrapper, &${ic.name}_HelperInput, &${ic.name}_HelperOutput) },`
    )
  }
  regen.add_raw(`    };
    if (segs.enter_path("api")) {
        std::string api;
        if (segs.enter_id(api)) {
            auto it = wrappers.find(api);
            if (it == wrappers.end()) {
              return false;
            }
            if (segs.end()) {
                std::string err;
                auto ret = std::get<0>(it->second)(obj, err);
                if (ret.has_value()) {
                    ctx.json_body(json::object { { "data", ret.value() } });
                } else {
                    ctx.json_body(json::object { { "error", err } });
                }
                return true;
            } else if (segs.enter_path("help") && segs.end()) {
                auto input = std::get<1>(it->second)();
                auto output = std::get<2>(it->second)();
                ctx.json_body(json::object { { "input", input }, { "output", output } });
                return true;
            }
        }
    } else if (segs.enter_path("help") && segs.end()) {
        json::object result;
        for (const auto& [ api, funcs ] : wrappers) {
            auto input = std::get<1>(funcs)();
            auto output = std::get<2>(funcs)();
            result[api] = json::object { { "input", input }, { "output", output } };
        }
        ctx.json_body(result);
        return true;
    }`)
  regen.add_raw('    return false;\n}')

  await regen.save(source_path)
}

main()
