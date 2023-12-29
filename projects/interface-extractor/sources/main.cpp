#include "clang-cpp.h"

#include <filesystem>
#include <iostream>
#include <meojson/json.hpp>
#include <set>

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

int main(int argc, char* argv[])
{
    auto index = clangpp::CXXIndex::make();
    index->create(0, 0);
    auto unit = clangpp::CXXTranslationUnit::make();
    unit->parse(index, argv[1],
                { "-I/opt/local/libexec/llvm-16/lib/clang/16/include",
                  "-IC:\\Program Files\\LLVM\\lib\\clang\\17\\include", "-Imaa/include", "-DLHG_PROCESS", "-std=c++20",
                  "-Wno-pragma-once-outside-header", "-x", "c++" },
                CXTranslationUnit_None);

    for (auto& diag : unit->getDiagnostics()) {
        auto [enable, disable] = diag.getOption();
        std::cout << diag.getSpelling() << ":" << enable << " " << disable << "\n";
    }

    auto cursor = unit->getCursor();

    auto decls = clangpp::select(
        { cursor }, clangpp::sel_recurse,
        [](const clangpp::CXXCursor& cur) { return cur.kind() == CXCursor_FunctionDecl; },
        [](const clangpp::CXXCursor& cur) {
            return clangpp::select({ cur }, clangpp::sel_direct, [](const clangpp::CXXCursor& cur) {
                       switch (cur.kind().raw_) {
                       case CXCursor_VisibilityAttr:
                           return cur.getSpelling() == "default";
                       case CXCursor_DLLImport:
                           return true;
                       default:
                           return false;
                       }
                       return false;
                   }).size() > 0;
        });

    json::array result;

    for (auto decl : decls) {
        auto name = decl.getSpelling();

        auto ret = decl.getResultType();
        auto args = decl.getArguments().value();
        json::array arguments;
        for (auto arg : args) {
            arguments.push_back(json::object { { "type", arg.getType().getCanonicalType().getSpelling() },
                                               { "name", arg.getSpelling() } });
        }
        result.push_back(json::object {
            { "name", name }, { "return", ret.getCanonicalType().getSpelling() }, { "argument", arguments } });
    }

    json::object output = { { "interface", result } };
    std::ofstream file("./generated/gen.interface.json");
    file << output.format(2);
    return 0;
}
