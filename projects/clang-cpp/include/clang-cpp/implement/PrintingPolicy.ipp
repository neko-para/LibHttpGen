#pragma once

namespace clangpp
{

inline CXXPrintingPolicy::CXXPrintingPolicy(CXPrintingPolicy raw)
{
    set(raw);
}

inline unsigned CXXPrintingPolicy::getProperty(CXPrintingPolicyProperty property) const
{
    return clang_PrintingPolicy_getProperty(raw_, property);
}

inline void CXXPrintingPolicy::setProperty(CXPrintingPolicyProperty property, unsigned value) const
{
    clang_PrintingPolicy_setProperty(raw_, property, value);
}

}
