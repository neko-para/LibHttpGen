#pragma once

#include <clang-c/Index.h>

#include <string>
#include <vector>

namespace clangpp::__private
{

template <typename Func>
struct VisitInfo
{
    std::function<Func>* func;
};

std::string wrap(const CXString& str, bool dispose = true)
{
    auto cstr = clang_getCString(str);
    std::string res(cstr);
    if (dispose) {
        clang_disposeString(str);
    }
    return res;
}

std::vector<std::string> wrap(CXStringSet* set)
{
    std::vector<std::string> res;
    if (!set) {
        return res;
    }
    for (unsigned i = 0; i < set->Count; i++) {
        res.emplace_back(wrap(set->Strings[i], false));
    }
    clang_disposeStringSet(set); // also dispose inner string
    return res;
}

}
