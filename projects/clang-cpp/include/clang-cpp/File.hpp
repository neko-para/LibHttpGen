#pragma once

#include "private.hpp"

namespace clangpp
{

struct CXXFile
{
    CXFile raw_;

    CXXFile(CXFile raw);

    operator bool() const;

    std::string getName() const;
    time_t getTime() const;
    int getUniqueID(CXFileUniqueID* outID) const;
    std::string tryGetRealPathName() const;
};

bool operator==(const CXXFile& a, const CXXFile& b);
bool operator!=(const CXXFile& a, const CXXFile& b);

}
