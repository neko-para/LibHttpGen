#pragma once

#include <algorithm>
#include <string>

namespace lhg::server
{

inline std::string segment_concat(const std::vector<std::string>& segs)
{
    if (segs.empty()) {
        return "/";
    }
    else {
        std::string result;
        for (const auto& seg : segs) {
            result.append("/");
            result.append(seg);
        }
        return result;
    }
}

inline std::vector<std::string> segment_split(const std::string& path)
{
    std::vector<std::string> segs;
    size_t left = 0;
    while (left < path.length()) {
        size_t right = path.find('/', left);
        if (right == std::string::npos) {
            segs.emplace_back(path.c_str() + left, path.length() - left);
            break;
        }
        if (left == right) {
            left = right + 1;
            continue;
        }
        segs.emplace_back(path.c_str() + left, right - left);
        left = right + 1;
    }
    return segs;
}

}
