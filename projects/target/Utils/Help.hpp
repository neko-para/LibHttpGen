#pragma once

#include <functional>

#include "Utils/Api.hpp"

namespace lhg
{

inline bool handle_help(Context& ctx, UrlSegments segs, const api_info_map& wrappers,
                        const std::vector<std::string>& opaques, std::function<void(json::object& )> callbacks)
{
    segs.reset();
    if (segs.enter_path("help") && segs.end()) {
        json::object result;

        help_api(result, wrappers);

        for (const auto& opaque : opaques) {
            result["/opaque/" + opaque] = { { "body", json::object {} }, { "response", { { ":id", "string" } } } };
        }

        callbacks(result);

        ctx.json_body(result);
        return true;
    }
    return false;
}

}
