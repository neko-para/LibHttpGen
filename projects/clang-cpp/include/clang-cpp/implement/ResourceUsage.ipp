#pragma once

namespace clangpp
{

struct ResourceUsage
{
    CXXResourceUsageKind kind;
    unsigned long amount;
};

namespace __private
{

    inline std::vector<ResourceUsage> wrap(CXTUResourceUsage usage)
    {
        std::vector<ResourceUsage> res;
        for (unsigned i = 0; i < usage.numEntries; i++) {
            res.push_back(ResourceUsage { usage.entries[i].kind, usage.entries[i].amount });
        }
        clang_disposeCXTUResourceUsage(usage);
        return res;
    }

}

inline std::string CXXResourceUsageKind::getName() const
{
    return clang_getTUResourceUsageName(raw_);
}

}
