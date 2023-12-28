#pragma once

#include "private.hpp"

namespace clangpp
{

struct CXXPrintingPolicy : public __private::CXXUniqueHolder<CXPrintingPolicy, clang_PrintingPolicy_dispose>
{
    using CXXUniqueHolder::CXXUniqueHolder;

    CXXPrintingPolicy(CXPrintingPolicy raw);

    unsigned getProperty(CXPrintingPolicyProperty property) const;
    void setProperty(CXPrintingPolicyProperty property, unsigned value) const;
};

}
