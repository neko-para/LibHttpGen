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
  remove: string[]
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
  const root = 'generated'
  const source_path = path.join(root, 'gen.wrapper.cpp')
  const config_path = path.join(root, 'config.json')
  const interface_path = path.join(root, 'gen.interface.json')
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
    regen.add_raw(`std::optional<json::object> ${ic.name}_Wrapper(json::object __param) {`)

    // callback
    let cbId: string | null = null
    let cbParam: string | null = null
    let ctxPos: number | null = null
    for (const [idx, arg] of ic.argument.entries()) {
      if (arg.type in callback_ids) {
        ctxPos = idx + cfg.callback[arg.type]!.pass
      }
    }

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
    ${type} *${arg.name};
    ${type}__OpaqueManager.del(${arg.name}_id, ${arg.name});`
          )
        } else {
          regen.add_sec(
            `lhg.impl.${ic.name}.arg.${arg.name}`,
            `    auto ${arg.name}_id = __param["${arg.name}"].as_string();
    auto ${arg.name} = ${type}__OpaqueManager.get(${arg.name}_id);`
          )
        }
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
    if (ic.return === 'void') {
      regen.add_sec(`lhg.impl.${ic.name}.final`, '    return json::object {};')
    } else {
      regen.add_sec(
        `lhg.impl.${ic.name}.final`,
        '    return json::object { { "return", to_json(__ret) } };'
      )
    }
    regen.add_raw('}\n')
  }

  regen.add_raw('bool handle_request(Context& ctx, UrlSegments segs) {')
  const convertPath = (str: string) => {
    return str
      .replace(/^./, match => match.toLowerCase())
      .replace(/([A-Z][a-z]+)/g, ' $1')
      .replace(/([A-Z]+)(?![A-Z])/g, ' $1')
      .split(/ +/)
      .map(part => part.toLowerCase())
  }
  for (const type in cfg.callback) {
    const cc = cfg.callback[type]!
    const ret = /^(.+) \(\*\)/.exec(type)![1]!
    regen.add_raw(`    // callback ${cc.name}`)
    regen.add_raw(`    segs.reset();
    if (segs.enter_path("${cc.name}")) {
        if (segs.enter_path("add")) {
            std::string id;
            ${cc.name}__Manager.alloc(id);
            ctx.json_body({ { "id", id } });
            return true;
        }
        if (segs.enter_path("del")) {
            auto body = json::parse(ctx.req_.body());
            auto& obj = body.value().as_object();
            std::string id = obj["id"].as_string();
            ${cc.name}__Manager.free(id);
            ctx.json_body({});
            return true;
        }
        std::string id;
        if (segs.enter_path("sub") && segs.enter_id(id)) {
            if (segs.enter_path("pull")) {
                auto __ctx = ${cc.name}__Manager.find(id);
                std::vector<std::string> cids;
                __ctx->take(cids);
                json::array obj_ids;
                for (const auto& cid: cids) {
                    obj_ids.push_back(cid);
                }
                ctx.json_body({{ "ids", obj_ids }});
                return true;
            }
            if (segs.enter_path("ctx")) {
                std::string cid;
                if (segs.enter_id(cid)) {
                    if (segs.enter_path("request")) {
                        auto __inst_ctx = ${cc.name}__Manager.find(id);
                        decltype(${cc.name}__Manager)::CallbackContext::args_type args;
                        __inst_ctx->get_args(cid, args);
${Array.from({ length: cc.all }, (_, k) => k)
  .filter(x => x != cc.self)
  .map(id => `                        auto v${id} = std::get<${id}>(args);`)
  .join('\n')}
                        json::object __arg = {
${Array.from({ length: cc.all }, (_, k) => k)
  .filter(x => x != cc.self)
  .map(id => `                            { "${cc.argn[id]}", v${id} },`)
  .join('\n')}
                        };
                        ctx.json_body(__arg);
                        return true;
                    }
                    if (segs.enter_path("response")) {
                        auto __inst_ctx = ${cc.name}__Manager.find(id);
${ret === 'void' ? '                        __inst_ctx->resp(cid, 0);' : ''}
                        return true;
                    }
                }
            }
        }
    }`)
  }
  for (const ic of int.interface) {
    const p = convertPath(ic.name)
    regen.add_raw(`    // ${ic.name} /${p.join('/')}
    segs.reset();`)
    regen.add_raw(`    if (${p.map(k => `segs.enter_path("${k}")`).join(' && ')} && segs.end()) {`)
    regen.add_raw(`        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = ${ic.name}_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;`)
    regen.add_raw('    }')
  }
  regen.add_raw('    return false;\n}')

  await regen.save(source_path)
}

main()
