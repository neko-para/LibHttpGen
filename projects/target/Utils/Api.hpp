#pragma once

#include <map>
#include <meojson/json.hpp>
#include <optional>

#include "Handle/Context.hpp"
#include "Helper/UrlSegments.hpp"

namespace lhg
{

using api_handle = std::optional<json::object> (*)(json::object, std::string&);
using api_helper_input = json::object (*)();
using api_helper_output = json::object (*)();

struct api_info
{
    api_handle handle;
    api_helper_input input;
    api_helper_output output;
};

using api_info_map = std::map<std::string, api_info>;

inline bool handle_api(Context& ctx, UrlSegments segs, json::object& obj, const api_info_map& wrappers)
{
    segs.reset();
    if (segs.enter_path("api")) {
        std::string api;
        if (segs.enter_id(api)) {
            auto it = wrappers.find(api);
            if (it == wrappers.end()) {
                return false;
            }
            if (segs.end()) {
                std::string err;
                auto ret = it->second.handle(obj, err);
                if (ret.has_value()) {
                    ctx.json_body(json::object { { "data", ret.value() } });
                }
                else {
                    ctx.json_body(json::object { { "error", err } });
                }
                return true;
            }
            else if (segs.enter_path("help") && segs.end()) {
                auto input = it->second.input();
                auto output = it->second.output();
                ctx.json_body(json::object { { "input", input }, { "output", output } });
                return true;
            }
        }
    }
    else if (segs.enter_path("help") && segs.end()) {
        json::object result;
        for (const auto& [api, info] : wrappers) {
            auto input = info.input();
            auto output = info.output();
            result[api] = json::object { { "input", input }, { "output", output } };
        }
        ctx.json_body(result);
        return true;
    }
    return false;
}

} // namespace lhg
