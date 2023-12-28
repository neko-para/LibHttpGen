#pragma once

namespace clangpp
{

inline CXXFile::CXXFile(CXFile raw) : raw_(raw) {}

inline CXXFile::operator bool() const
{
    return raw_;
}

inline std::string CXXFile::getName() const
{
    return __private::wrap(clang_getFileName(raw_));
}

inline time_t CXXFile::getTime() const
{
    return clang_getFileTime(raw_);
}

inline int CXXFile::getUniqueID(CXFileUniqueID* outID) const
{
    return clang_getFileUniqueID(raw_, outID);
}

inline std::string CXXFile::tryGetRealPathName() const
{
    return __private::wrap(clang_File_tryGetRealPathName(raw_));
}

inline bool operator==(const CXXFile& a, const CXXFile& b)
{
    return clang_File_isEqual(a.raw_, b.raw_);
}

inline bool operator!=(const CXXFile& a, const CXXFile& b)
{
    return !(a == b);
}

}
