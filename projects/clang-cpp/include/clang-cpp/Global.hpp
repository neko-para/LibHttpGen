#pragma once

#include "private.hpp"

namespace clangpp
{

inline std::string getClangVersin()
{
    return __private::wrap(clang_getClangVersion());
}

}
