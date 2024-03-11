import fs from 'fs/promises'

import { loadConfig, loadInterface } from './config'

async function main() {
  const int = await loadInterface()
  const cfg = await loadConfig()

  const result: string[] = []

  result.push('#pragma once')
  result.push('')
  result.push(`#include "function/interface.hpp"`)
  result.push('')
  if (cfg.header) {
    for (const hdr of cfg.header) {
      result.push(`#include "${hdr}"`)
    }
    result.push('')
  }
  result.push('namespace lhg {')
  result.push('')
  result.push(`namespace ${cfg.name} {`)
  result.push('')

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

  for (const info of int.interface) {
    result.push(`struct func_type_${info.name} {`)
    for (const [idx, arg] of info.argument.entries()) {
      result.push(`  struct _${idx}_${arg.name} {`)
      result.push(`    constexpr static size_t index = ${idx};`)
      result.push(`    constexpr static const char* name = "${arg.name}";`)
      result.push(`    using type = ${arg.type};`)
      result.push('  };')
    }
    result.push(`  struct ret {`)
    result.push(`    constexpr static size_t index = ${info.argument.length};`)
    result.push(`    constexpr static const char* name = "return";`)
    result.push(`    using type = ${info.return};`)
    result.push('  };')
    result.push(
      `  using args = std::tuple<${info.argument
        .map((v, i) => `_${i}_${v.name}`)
        .concat(['ret'])
        .join(', ')}>;`
    )

    result.push('};')

    result.push(`struct function_${info.name} {`)
    result.push(`  constexpr static auto func = ${info.name};`)
    result.push(`  constexpr static const char* name = "${info.name}";`)
    result.push(`  using type = func_type_${info.name};`)
    result.push('};')
    result.push('')
  }

  result.push(`using __function_list = std::tuple<
${int.interface.map(info => `  function_${info.name}`).join(',\n')}
>;`)

  result.push('')
  result.push(`}`)
  result.push('')

  for (const info of int.interface) {
    result.push('template<>')
    result.push(`struct is_input<${cfg.name}::func_type_${info.name}::ret, false> {`)
    result.push('  constexpr static bool value = false;')
    result.push('  using type = std::monostate;')
    result.push('};')
    result.push('template<>')
    result.push(`struct is_output<${cfg.name}::func_type_${info.name}::ret, false> {`)
    result.push('  constexpr static bool value = true;')
    result.push(`  using type = ${cfg.name}::func_type_${info.name}::ret::type;`)
    result.push('};')
    result.push('')
  }

  result.push('')
  result.push(`}`)

  fs.writeFile('../info.hpp', result.join('\n'))
}

main()
