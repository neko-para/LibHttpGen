#pragma once

#include "private.hpp"

namespace clangpp
{

struct CXXIndex : public __private::CXXUniqueHolder<CXIndex, clang_disposeIndex>
{
    using CXXUniqueHolder::CXXUniqueHolder;

    static std::shared_ptr<CXXIndex> make();

    void create(int excludeDeclarationsFromPCH, int displayDiagnostics);
    void createWithOptions(const CXIndexOptions* options);

    unsigned getGlobalOptions() const;
    void setInvocationEmissionPathOption(const std::string& path) const;
};

}
