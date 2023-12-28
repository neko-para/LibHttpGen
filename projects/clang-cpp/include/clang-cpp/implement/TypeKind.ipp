#pragma once

namespace clangpp
{

inline bool CXXTypeKind::isBuiltin() const
{
    return CXType_FirstBuiltin <= raw_ && raw_ <= CXType_LastBuiltin;
}

inline std::string CXXTypeKind::getSpelling() const
{
    return __private::wrap(clang_getTypeKindSpelling(raw_));
}

}
