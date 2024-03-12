import fs from 'fs/promises'

import { loadConfig, loadInterface } from './config'

function parseFuncPtr(type: string) {
  const mat = /^\s*([^(]+?)?\s*\(\*\)\(([\s\S]*)\)$/.exec(type)
  if (!mat) {
    throw 'bad func ptr type ' + type
  }
  const ret = mat[1]!
  const args_list = mat[2]!
  // TODO: allow func ptr inside arg
  const args = args_list.split(',')
  return {
    ret,
    args
  }
}

async function main() {
  const int = await loadInterface()
  const cfg = await loadConfig()

  const result: string[] = []

  result.push('#pragma once')
  result.push('')
  result.push(`#include "function/interface.hpp"`)
  result.push(`#include "callback/interface.hpp"`)
  result.push('')
  if (cfg.header) {
    for (const hdr of cfg.header) {
      result.push(`#include "${hdr}"`)
    }
    result.push('')
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

  for (const info of int.interface) {
    result.push(`namespace lhg::${cfg.name} {`)
    result.push('')
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

    result.push('}')
    result.push('namespace lhg::call {')
    result.push('')

    result.push('template<>')
    result.push(`struct is_input<${cfg.name}::func_type_${info.name}::ret, false> {`)
    result.push('  constexpr static bool value = false;')
    result.push('};')
    result.push('template<>')
    result.push(`struct is_output<${cfg.name}::func_type_${info.name}::ret, false> {`)
    result.push('  constexpr static bool value = true;')
    result.push('};')

    result.push('')
    result.push('}')
    result.push('')
  }

  result.push(`namespace lhg::${cfg.name} {`)
  result.push('')
  result.push(`using __function_list = std::tuple<
${int.interface.map(info => `  function_${info.name}`).join(',\n')}
>;`)
  result.push('')
  result.push('}')

  for (const [type, info] of Object.entries(cfg.callback)) {
    result.push(`namespace lhg::${cfg.name} {`)
    result.push('')

    const { ret, args } = parseFuncPtr(type)
    result.push(`struct func_type_${info.name} {`)

    for (const [idx, arg] of args.entries()) {
      result.push(`  struct _${idx}_${info.arg_name[idx]} {`)
      result.push(`    constexpr static size_t index = ${idx};`)
      result.push(`    constexpr static const char* name = "${info.arg_name[idx]}";`)
      result.push(`    using type = ${arg};`)
      result.push('  };')
    }

    result.push(`  struct ret {`)
    result.push(`    constexpr static size_t index = ${args.length};`)
    result.push(`    constexpr static const char* name = "return";`)
    result.push(`    using type = ${ret};`)
    result.push('  };')
    result.push(
      `  using args = std::tuple<${info.arg_name
        .map((v, i) => `_${i}_${v}`)
        .concat(['ret'])
        .join(', ')}>;`
    )

    result.push(
      `};
struct callback_${info.name} {
  using type = func_type_${info.name};
  using func_type = ${type};
  constexpr static size_t context = ${info.self};
};`
    )

    result.push('')
    result.push(`}`)
    result.push('namespace lhg::callback {')
    result.push('')

    result.push('template<>')
    result.push(`struct is_input<${cfg.name}::func_type_${info.name}::_${info.self}_, false> {`)
    result.push('  constexpr static bool value = false;')
    result.push('};')
    result.push('template<>')
    result.push(`struct is_input<${cfg.name}::func_type_${info.name}::ret, false> {`)
    result.push('  constexpr static bool value = false;')
    result.push('};')
    result.push('template<>')
    result.push(`struct is_output<${cfg.name}::func_type_${info.name}::ret, false> {`)
    result.push('  constexpr static bool value = true;')
    result.push('};')

    result.push('')
    result.push('}')
    result.push('')
  }

  result.push('namespace lhg::call {')

  for (const opaque in cfg.opaque) {
    result.push(
      `template<>
struct type_is_handle<${opaque} *, false> {
  constexpr static bool value = true;
};`
    )
  }

  result.push('')
  result.push(`}`)

  fs.writeFile('../info.hpp', result.join('\n'))
}

main()
