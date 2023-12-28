#pragma once

#include "private.hpp"

namespace clangpp
{

struct ResourceUsage;

struct CXXResourceUsageKind : public __private::CXXEnumHolder<CXTUResourceUsageKind>
{
    using CXXEnumHolder::CXXEnumHolder;

    std::string getName() const;
};

namespace __private
{

    std::vector<ResourceUsage> wrap(CXTUResourceUsage usage);

}

}
