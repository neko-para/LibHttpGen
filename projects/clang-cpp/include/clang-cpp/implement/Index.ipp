#pragma once

namespace clangpp
{

inline std::shared_ptr<CXXIndex> CXXIndex::make()
{
    return std::make_shared<CXXIndex>();
}

inline void CXXIndex::create(int excludeDeclarationsFromPCH, int displayDiagnostics)
{
    set(clang_createIndex(excludeDeclarationsFromPCH, displayDiagnostics));
}

inline void CXXIndex::createWithOptions(const CXIndexOptions* options)
{
    set(clang_createIndexWithOptions(options));
}

inline unsigned CXXIndex::getGlobalOptions() const
{
    return clang_CXIndex_getGlobalOptions(raw_);
}

inline void CXXIndex::setInvocationEmissionPathOption(const std::string& path) const
{
    clang_CXIndex_setInvocationEmissionPathOption(raw_, path.c_str());
}

}
