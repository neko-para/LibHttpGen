#ifndef USE_FMTLIB
#define USE_FMTLIB
#endif

#include <iostream>
#include <lhgfmt.h>
#include <map>
#include <meojson/json.hpp>

#include "LHGRegenerator.h"

struct CallbackConfig
{
    int argOffset;
    int ctxPos;
};

std::string read_file(std::filesystem::path path)
{
    std::ifstream in(path);
    if (!in.is_open()) {
        return {};
    }
    std::stringstream ss;
    ss << in.rdbuf();
    in.close();

    return ss.str();
}

const std::string sectionIdPadding = "// LHG SEC ID ";
int main(int argc, char* argv[])
{
    auto target = std::filesystem::path("./generated/gen.wrapper.cpp");
    lhg::Regenerator regen;

    regen.section_helper = {
        "// LHG SEC BEGIN",
        "// LHG SEC END",
        "// LHG SEC DEF",
        [](std::string content) -> std::string {
            if (content.starts_with(sectionIdPadding)) {
                return content.substr(sectionIdPadding.length());
            }
            else {
                return {};
            }
        },
        [](std::string content) -> std::string { return sectionIdPadding + content; },
    };

    regen.load(target);

    regen.append_fixed("// clang-format off");
    regen.append_fixed("");
    regen.append_fixed("#include \"helper.h\"");
    regen.append_fixed("");
    regen.append_section("lhg.include", "");
    regen.append_fixed("");
    regen.append_section("lhg.custom.global", "");
    regen.append_fixed("");

    auto data = json::parse(read_file(std::filesystem::path("./generated/gen.interface.json")))
                    .value_or(json::object {
                        { "config", json::object { { "callback", json::object {} }, { "opacity", json::array {} } } },
                        { "interface", json::array {} } })
                    .as_object();
    json::array interfaces = data["interface"].as_array();
    json::object config = data["config"].as_object();

    int callback_type_counter = 0;
    std::map<std::string, int> callback_type_id;
    std::map<std::string, CallbackConfig> callback_configs;
    for (const auto& [key, cfg] : config["callback"].as_object()) {
        auto c = cfg.as_object();
        auto& cc = callback_configs[key];
        cc = {
            c["pass"].as_integer(),
            c["self"].as_integer(),
        };
        callback_type_id[key] = ++callback_type_counter;

        regen.append_fixed(
            LHGFMT::format("static callback_manager<{}> Callback{}__Manager;", key, callback_type_counter));
        regen.append_fixed("");
        // regen.append_fixed("static ");
    }

    for (json::value v : interfaces) {
        json::object interface = v.as_object();

        json::array args = interface["argument"].as_array();
        std::string ret = interface["return"].as_string();
        std::string name = interface["name"].as_string();

        // std::cout << LHGFMT::format("process {}\n", name);

        int arg_cnt = args.size();

        regen.append_fixed(LHGFMT::format("std::optional<json::object> {}_Wrapper(json::object __param) {{", name));
        for (int i = 0; i < arg_cnt; i++) {
            std::string aname = args[i].as_object()["name"].as_string();
            std::string atype = args[i].as_object()["type"].as_string();
            regen.append_section(
                LHGFMT::format("lhg.impl.{}.arg.{}", name, i),
                LHGFMT::format(
                    "    auto {}_temp = from_json<{}>(__param[\"{}\"]);\n    auto {} = from_json_fix<{}>({}_temp);\n",
                    aname, atype, aname, aname, atype, aname));
        }
        if (ret != "void") {
            regen.append_fixed(LHGFMT::format("    auto __return = {}(", name));
        }
        else {
            regen.append_fixed(LHGFMT::format("    {}(", name));
        }
        for (int i = 0; i < arg_cnt; i++) {
            std::string aname = args[i].as_object()["name"].as_string();
            regen.append_fixed(LHGFMT::format("        {}{}", aname, i == (arg_cnt - 1) ? "" : ","));
        }
        regen.append_fixed("    );");
        if (ret != "void") {
            regen.append_section(LHGFMT::format("lhg.impl.{}.return", name), "    auto __ret = __return;\n");
        }
        else {
            regen.append_section(LHGFMT::format("lhg.impl.{}.return", name), "");
        }
        if (ret != "void") {
            regen.append_section(LHGFMT::format("lhg.impl.{}", name),
                                 "    return json::object { { \"return\",  to_json(__ret) } };\n");
        }
        else {
            regen.append_section(LHGFMT::format("lhg.impl.{}", name), "    return json::object {};\n");
        }
        regen.append_fixed("}");
        regen.append_fixed("");
    }

    regen.save(target);
}
