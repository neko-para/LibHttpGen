"use strict";
var __create = Object.create;
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __getProtoOf = Object.getPrototypeOf;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __copyProps = (to, from, except, desc) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
  }
  return to;
};
var __toESM = (mod, isNodeMode, target) => (target = mod != null ? __create(__getProtoOf(mod)) : {}, __copyProps(
  // If the importer is in node compatibility mode or this is not an ESM
  // file that has been converted to a CommonJS file using a Babel-
  // compatible transform (i.e. "__esModule" has not been set), then set
  // "default" to the CommonJS "module.exports" for node compatibility.
  isNodeMode || !mod || !mod.__esModule ? __defProp(target, "default", { value: mod, enumerable: true }) : target,
  mod
));

// src/new.ts
var import_promises2 = __toESM(require("fs/promises"));

// src/config.ts
var import_promises = __toESM(require("fs/promises"));
async function loadConfig(config_path) {
  const obj = JSON.parse(await import_promises.default.readFile(config_path, "utf-8"));
  return {
    name: obj.name ?? "unknown",
    header: obj.header ?? [],
    callback: obj.callback ?? {},
    opaque: obj.opaque ?? {},
    output: obj.output ?? [],
    remove: obj.remove ?? [],
    check: obj.check ?? {}
  };
}
async function loadInterface(interface_path) {
  return JSON.parse(await import_promises.default.readFile(interface_path, "utf-8"));
}

// src/new.ts
function parseFuncPtr(type) {
  const mat = /^\s*([^(]+?)?\s*\(\*\)\(([\s\S]*)\)$/.exec(type);
  if (!mat) {
    throw "bad func ptr type " + type;
  }
  const ret = mat[1];
  const args_list = mat[2];
  const args = args_list.split(",");
  return {
    ret,
    args
  };
}
async function main() {
  let interface_path = process.argv[2] ?? "../interface.json";
  let config_path = process.argv[3] ?? "../config.json";
  let output_path = process.argv[4] ?? "../info.hpp";
  const int = await loadInterface(interface_path);
  const cfg = await loadConfig(config_path);
  int.interface = int.interface.filter((x) => {
    for (const rule of cfg.remove) {
      if (rule.startsWith("/")) {
        if (new RegExp(rule.slice(1)).exec(x.name)) {
          return false;
        }
      } else {
        if (rule === x.name) {
          return false;
        }
      }
    }
    return true;
  });
  const result = [];
  result.push("// clang-format off");
  result.push("#pragma once");
  result.push("");
  result.push('#include "function/interface.hpp"');
  result.push('#include "callback/interface.hpp"');
  result.push('#include "utils/general.hpp"');
  result.push("");
  if (cfg.header) {
    for (const hdr of cfg.header) {
      result.push(`#include "${hdr}"`);
    }
    result.push("");
  }
  for (const info of int.interface) {
    result.push(`namespace lhg::${cfg.name} {`);
    result.push("");
    result.push(`struct func_type_${info.name} {`);
    for (const [idx, arg] of info.argument.entries()) {
      result.push(`  struct _${idx}_${arg.name} {`);
      result.push(`    constexpr static size_t index = ${idx};`);
      result.push(`    constexpr static const char* name = "${arg.name}";`);
      result.push(`    using type = ${arg.type};`);
      result.push("  };");
    }
    result.push(`  struct ret {`);
    result.push(`    constexpr static size_t index = ${info.argument.length};`);
    result.push(`    constexpr static const char* name = "return";`);
    result.push(`    using type = ${info.return};`);
    result.push("  };");
    result.push(
      `  using args = std::tuple<${info.argument.map((v, i) => `_${i}_${v.name}`).concat(["ret"]).join(", ")}>;`
    );
    result.push("};");
    result.push(`struct function_${info.name} {`);
    result.push(`  constexpr static auto func = ${info.name};`);
    result.push(`  constexpr static const char* name = "${info.name}";`);
    result.push(`  using type = func_type_${info.name};`);
    result.push("};");
    result.push("");
    result.push("}");
    result.push("namespace lhg::call {");
    result.push("");
    result.push("template<>");
    result.push(`struct is_input<${cfg.name}::func_type_${info.name}::ret, false> {`);
    result.push("  constexpr static bool value = false;");
    result.push("};");
    result.push("template<>");
    result.push(`struct is_output<${cfg.name}::func_type_${info.name}::ret, false> {`);
    result.push("  constexpr static bool value = true;");
    result.push("};");
    result.push("");
    result.push("}");
    result.push("");
  }
  result.push(`namespace lhg::${cfg.name} {`);
  result.push("");
  result.push(`using __function_list = std::tuple<
${int.interface.map((info) => `  function_${info.name}`).join(",\n")}
>;`);
  result.push("");
  result.push("}");
  for (const [type, info] of Object.entries(cfg.callback)) {
    result.push(`namespace lhg::${cfg.name} {`);
    result.push("");
    const { ret, args } = parseFuncPtr(type);
    result.push(`struct func_type_${info.name} {`);
    for (const [idx, arg] of args.entries()) {
      result.push(`  struct _${idx}_${info.arg_name[idx]} {`);
      result.push(`    constexpr static size_t index = ${idx};`);
      result.push(`    constexpr static const char* name = "${info.arg_name[idx]}";`);
      result.push(`    using type = ${arg};`);
      result.push("  };");
    }
    result.push(`  struct ret {`);
    result.push(`    constexpr static size_t index = ${args.length};`);
    result.push(`    constexpr static const char* name = "return";`);
    result.push(`    using type = ${ret};`);
    result.push("  };");
    result.push(
      `  using args = std::tuple<${info.arg_name.map((v, i) => `_${i}_${v}`).concat(["ret"]).join(", ")}>;`
    );
    result.push(
      `};
struct callback_${info.name} {
  using type = func_type_${info.name};
  using func_type = ${type};
  constexpr static size_t context = ${info.self};
  constexpr static const char* name = "${info.name}";
};`
    );
    result.push("");
    result.push(`}`);
    result.push("namespace lhg::callback {");
    result.push("");
    result.push("template<>");
    result.push(`struct is_input<${cfg.name}::func_type_${info.name}::_${info.self}_, false> {`);
    result.push("  constexpr static bool value = false;");
    result.push("};");
    result.push("template<>");
    result.push(`struct is_input<${cfg.name}::func_type_${info.name}::ret, false> {`);
    result.push("  constexpr static bool value = false;");
    result.push("};");
    result.push("template<>");
    result.push(`struct is_output<${cfg.name}::func_type_${info.name}::ret, false> {`);
    result.push("  constexpr static bool value = true;");
    result.push("};");
    result.push("");
    result.push("}");
    result.push("");
  }
  result.push(`namespace lhg::${cfg.name} {`);
  result.push("");
  result.push(
    `using __callback_list = std::tuple<
${Object.entries(cfg.callback).map((info) => `  callback_${info[1].name}`).join(",\n")}
>;`
  );
  result.push("");
  result.push("}");
  result.push("");
  for (const opaque in cfg.opaque) {
    result.push(
      `namespace lhg::call {

template<>
struct type_is_handle<${opaque} *, false> {
  constexpr static bool value = true;
};

}
namespace lhg::callback {

template<>
struct type_is_handle<${opaque} *, false> {
  constexpr static bool value = true;
};

}
namespace lhg {

template<>
struct handle_name<${opaque} *> {
  constexpr static const char* name = "${opaque}";
};

}
`
    );
  }
  result.push(`namespace lhg::${cfg.name} {`);
  result.push("");
  result.push(
    `using __handle_list = std::tuple<${Object.keys(cfg.opaque).map((info) => `${info}*`).join(", ")}>;`
  );
  result.push("");
  result.push("}");
  result.push("");
  import_promises2.default.writeFile(output_path, result.join("\n"));
}
main();
//# sourceMappingURL=new.js.map
