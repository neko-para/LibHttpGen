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
    if (argc < 2) {
        std::cerr << "No source provided.";
        return 1;
    }
    std::vector<const char*> options;
    for (int i = 2; i < argc; i++) {
        options.push_back(argv[i]);
    }

    auto index = clangpp::CXXIndex::make();
    index->create(0, 0);
    auto unit = clangpp::CXXTranslationUnit::make();
    options.push_back("-DLHG_PROCESS");
    options.push_back("-Wno-pragma-once-outside-header");
    options.push_back("-std=c++20");
    options.push_back("-x");
    options.push_back("c++");
    auto err = unit->parse(index, argv[1], options, CXTranslationUnit_None);

    for (auto& diag : unit->getDiagnostics()) {
        auto [enable, disable] = diag.getOption();
        std::cout << diag.getSpelling() << ":" << enable << " " << disable << "\n";
    }

    if (err) {
        return 1;
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
