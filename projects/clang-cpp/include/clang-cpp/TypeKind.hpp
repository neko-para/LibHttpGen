#pragma once

#include "private.hpp"

namespace clangpp
{

struct CXXTypeKind : public __private::CXXEnumHolder<CXTypeKind>
{
    using CXXEnumHolder::CXXEnumHolder;

    bool isBuiltin() const;

    std::string getSpelling() const;
};

}
