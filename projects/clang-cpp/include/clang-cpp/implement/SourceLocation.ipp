#pragma once

namespace clangpp
{

struct SourceLocationFile
{
    CXXFile file;
    unsigned line, column, offset;
};

struct SourceLocationPath
{
    std::string filename;
    unsigned line, column;
};

inline CXXSourceLocation::CXXSourceLocation()
{
    raw_ = clang_getNullLocation();
}

inline CXXSourceLocation::CXXSourceLocation(const CXSourceLocation& raw) : raw_(raw) {}

inline int CXXSourceLocation::isInSystemHeader() const
{
    return clang_Location_isInSystemHeader(raw_);
}

inline int CXXSourceLocation::isFromMainFile() const
{
    return clang_Location_isFromMainFile(raw_);
}

inline SourceLocationFile CXXSourceLocation::getExpansionLocation() const
{
    CXFile file;
    unsigned line, column, offset;
    clang_getExpansionLocation(raw_, &file, &line, &column, &offset);
    return SourceLocationFile { CXXFile(file), line, column, offset };
}

inline SourceLocationPath CXXSourceLocation::getPresumedLocation() const
{
    CXString filename;
    unsigned line, column;
    clang_getPresumedLocation(raw_, &filename, &line, &column);
    return SourceLocationPath { __private::wrap(filename), line, column };
}

inline SourceLocationFile CXXSourceLocation::getSpellingLocation() const
{
    CXFile file;
    unsigned line, column, offset;
    clang_getSpellingLocation(raw_, &file, &line, &column, &offset);
    return SourceLocationFile { CXXFile(file), line, column, offset };
}

inline SourceLocationFile CXXSourceLocation::getFileLocation() const
{
    CXFile file;
    unsigned line, column, offset;
    clang_getFileLocation(raw_, &file, &line, &column, &offset);
    return SourceLocationFile { CXXFile(file), line, column, offset };
}

inline bool operator==(const CXXSourceLocation& a, const CXXSourceLocation& b)
{
    return clang_equalLocations(a.raw_, b.raw_);
}

inline bool operator!=(const CXXSourceLocation& a, const CXXSourceLocation& b)
{
    return !(a == b);
}

} // namespace clangpp
