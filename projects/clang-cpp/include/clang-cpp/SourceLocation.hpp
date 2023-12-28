#pragma once

#include "File.hpp"
#include "private.hpp"

namespace clangpp
{

struct SourceLocationFile;
struct SourceLocationPath;

struct CXXSourceLocation
{
    CXSourceLocation raw_;

    CXXSourceLocation();
    CXXSourceLocation(const CXSourceLocation& raw);

    int isInSystemHeader() const;
    int isFromMainFile() const;

    SourceLocationFile getExpansionLocation() const;
    SourceLocationPath getPresumedLocation() const;
    SourceLocationFile getSpellingLocation() const;
    SourceLocationFile getFileLocation() const;
};

bool operator==(const CXXSourceLocation& a, const CXXSourceLocation& b);
bool operator!=(const CXXSourceLocation& a, const CXXSourceLocation& b);

} // namespace clangpp
