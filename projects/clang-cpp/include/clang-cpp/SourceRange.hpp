#pragma once

#include "SourceLocation.hpp"
#include "private.hpp"

namespace clangpp
{

struct CXXSourceRange
{
    CXSourceRange raw_;

    CXXSourceRange();
    CXXSourceRange(const CXXSourceLocation& begin, const CXXSourceLocation& end);
    CXXSourceRange(const CXSourceRange& raw);

    int isNull() const;
    operator bool() const;

    CXXSourceLocation getStart() const;
    CXXSourceLocation getEnd() const;
};

bool operator==(const CXXSourceRange& a, const CXXSourceRange& b);
bool operator!=(const CXXSourceRange& a, const CXXSourceRange& b);

namespace __private
{

    std::vector<CXXSourceRange> wrap(CXSourceRangeList* lst);

}

} // namespace clangpp
