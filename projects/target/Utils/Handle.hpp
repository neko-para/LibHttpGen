#pragma once

#include <meojson/json.hpp>

#include "Handle/Context.hpp"
#include "Helper/HandleManager.hpp"
#include "Helper/UrlSegments.hpp"

namespace lhg
{

template <typename F>
using opaque_manager = HandleManager<F>;

template <typename HM>
inline bool handle_opaque(const char* name, HM& manager, Context& ctx, UrlSegments segs, json::object& obj)
{
    segs.reset();
    if (segs.enter_path("opaque")) {
        if (segs.enter_path(name)) {
            if (segs.end()) {
                auto mp = manager.dump();
                json::object data;
                for (const auto& [id, handle] : mp) {
                    data[id] = json::object { { "pointer", reinterpret_cast<size_t>(handle) } };
                }
                ctx.json_body({ { "data", data } });
                return true;
            }
        }
    }
    return false;
}

}
