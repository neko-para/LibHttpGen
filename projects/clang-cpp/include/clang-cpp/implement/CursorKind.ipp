#pragma once

namespace clangpp
{

inline unsigned CXXCursorKind::isDeclaration() const
{
    return clang_isDeclaration(raw_);
}

inline unsigned CXXCursorKind::isReference() const
{
    return clang_isReference(raw_);
}

inline unsigned CXXCursorKind::isExpression() const
{
    return clang_isExpression(raw_);
}

inline unsigned CXXCursorKind::isStatement() const
{
    return clang_isStatement(raw_);
}

inline unsigned CXXCursorKind::isAttribute() const
{
    return clang_isAttribute(raw_);
}

inline unsigned CXXCursorKind::isInvalid() const
{
    return clang_isInvalid(raw_);
}

inline unsigned CXXCursorKind::isTranslationUnit() const
{
    return clang_isTranslationUnit(raw_);
}

inline unsigned CXXCursorKind::isPreprocessing() const
{
    return clang_isPreprocessing(raw_);
}

inline unsigned CXXCursorKind::isUnexposed() const
{
    return clang_isUnexposed(raw_);
}

inline std::string CXXCursorKind::getSpelling() const
{
    return __private::wrap(clang_getCursorKindSpelling(raw_));
}

}
