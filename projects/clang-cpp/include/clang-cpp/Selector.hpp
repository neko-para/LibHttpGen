#include "private.hpp"

namespace clangpp
{

inline std::vector<CXXCursor> select(const std::vector<CXXCursor>& current)
{
    return current;
}

template <typename... Args>
inline std::vector<CXXCursor> select(const std::vector<CXXCursor>& current,
                                     std::function<std::vector<CXXCursor>(const CXXCursor&)> recurse,
                                     const Args&... args)
{
    std::vector<CXXCursor> result;
    for (const auto& cur : current) {
        auto res = recurse(cur);
        std::copy_if(res.begin(), res.end(), std::back_inserter(result), [&](const CXXCursor& cur) {
            return std::find(result.begin(), result.end(), cur) == result.end();
        });
    }
    return select(result, args...);
}

template <typename... Args>
inline std::vector<CXXCursor> select(const std::vector<CXXCursor>& current,
                                     std::function<bool(const CXXCursor&)> filter, const Args&... args)
{
    std::vector<CXXCursor> result;
    std::copy_if(current.begin(), current.end(), std::back_inserter(result), filter);
    return select(result, args...);
}

inline std::vector<CXXCursor> sel_recurse(const CXXCursor& cur)
{
    std::vector<CXXCursor> result;
    cur.visitChildren([&result](CXXCursor cur, CXXCursor) {
        result.push_back(cur);
        return CXChildVisit_Recurse;
    });
    return result;
}

inline std::vector<CXXCursor> sel_direct(const CXXCursor& cur)
{
    std::vector<CXXCursor> result;
    cur.visitChildren([&result](CXXCursor cur, CXXCursor) {
        result.push_back(cur);
        return CXChildVisit_Continue;
    });
    return result;
}

}
