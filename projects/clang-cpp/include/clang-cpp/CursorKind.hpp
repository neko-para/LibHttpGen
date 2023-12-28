#pragma once

#include "private.hpp"

namespace clangpp
{

struct CXXCursorKind : public __private::CXXEnumHolder<CXCursorKind>
{
    using CXXEnumHolder::CXXEnumHolder;

    unsigned isDeclaration() const;
    unsigned isReference() const;
    unsigned isExpression() const;
    unsigned isStatement() const;
    unsigned isAttribute() const;
    unsigned isInvalid() const;
    unsigned isTranslationUnit() const;
    unsigned isPreprocessing() const;
    unsigned isUnexposed() const;

    std::string getSpelling() const;
};

}
