#pragma once

#include <functional>

#include "Utils/Api.hpp"

namespace lhg
{

inline bool handle_help(Context& ctx, UrlSegments segs, const api_info_map& wrappers,
                        const std::vector<std::string>& opaques, std::function<void(json::object&)> callbacks)
{
    segs.reset();
    if (segs.enter_path("help") && segs.end()) {
        json::object result;

        help_api(result, wrappers);

        for (const auto& opaque : opaques) {
            result["/opaque/" + opaque] =
                wrap_oper({}, { { "type", "object" }, { "additionalProperties", { { "type", "string" } } } });
        }

        callbacks(result);

        ctx.json_body(
            { { "openapi", "3.0" }, { "info", { { "title", "lhg" }, { "version", "1.0" } } }, { "paths", result } });
        return true;
    }
    return false;
}

}
