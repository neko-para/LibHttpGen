#pragma once

namespace clangpp
{

namespace __private
{

    inline std::vector<CXXSourceRange> wrap(CXSourceRangeList* lst)
    {
        std::vector<CXXSourceRange> res;
        if (!lst) {
            return res;
        }
        for (unsigned i = 0; i < lst->count; i++) {
            res.emplace_back(lst->ranges[i]);
        }
        clang_disposeSourceRangeList(lst);
        return res;
    }

}

inline CXXSourceRange::CXXSourceRange()
{
    raw_ = clang_getNullRange();
}

inline CXXSourceRange::CXXSourceRange(const CXXSourceLocation& begin, const CXXSourceLocation& end)
{
    raw_ = clang_getRange(begin.raw_, end.raw_);
}

inline CXXSourceRange::CXXSourceRange(const CXSourceRange& raw) : raw_(raw) {}

inline int CXXSourceRange::isNull() const
{
    return clang_Range_isNull(raw_);
}

inline CXXSourceRange::operator bool() const
{
    return !isNull();
}

inline CXXSourceLocation CXXSourceRange::getStart() const
{
    return clang_getRangeStart(raw_);
}

inline CXXSourceLocation CXXSourceRange::getEnd() const
{
    return clang_getRangeEnd(raw_);
}

inline bool operator==(const CXXSourceRange& a, const CXXSourceRange& b)
{
    return clang_equalRanges(a.raw_, b.raw_);
}

inline bool operator!=(const CXXSourceRange& a, const CXXSourceRange& b)
{
    return !(a == b);
}

}
