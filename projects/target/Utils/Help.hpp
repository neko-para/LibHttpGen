#pragma once

#include <functional>

#include "Utils/Api.hpp"

namespace lhg
{

inline void help_callback(const char* name, json::object& result, const json::object& arg,
                          const std::optional<json::object>& ret)
{
    std::string prefix = std::string("/callback/") + name + "/";
    auto id_cid = json::object { { "id", { { "type", "string" } } }, { "cid", { { "type", "string" } } } };
    result[prefix + "dump"] = wrap_oper(
        {}, { { "type", "object" },
              { "properties",
                { { "data",
                    { { "type", "object" },
                      { "properties",
                        { { "ids", { { "type", "array" }, { "items", { { "type", "string" } } } } } } } } } } } });
    result[prefix + "add"] = wrap_oper(
        {}, { { "type", "object" },
              { "properties",
                { { "data", { { "type", "object" }, { "properties", { { "id", { { "type", "string" } } } } } } } } } });
    result[prefix + "del"] = wrap_oper(
        { { "type", "object" }, { "properties", { { "id", { { "type", "string" } } } } } },
        { { "type", "object" }, { "properties", { { "data", {} }, { "error", { { "type", "string" } } } } } });
    result[prefix + "pull"] =
        wrap_oper({ { "type", "object" }, { "properties", { { "id", { { "type", "string" } } } } } },
                  { { "type", "object" },
                    { "properties",
                      { { "data", { { "ids", { { "type", "array" }, { "items", { { "type", "string" } } } } } } },
                        { "error", { { "type", "string" } } } } } });
    result[prefix + "request"] = wrap_oper(
        { { "type", "object" }, { "properties", id_cid } },
        { { "type", "object" },
          { "properties",
            { { "data", { { "type", "object" }, { "properties", arg } } }, { "error", { { "type", "string" } } } } } });
    result[prefix + "response"] = wrap_oper(
        { { "type", "object" },
          { "properties", ret.has_value() ? (id_cid | json::object { { "return", ret.value() } }) : id_cid } },
        { { "data", json::object {} }, { "error", { { "type", "string" } } } });
}

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
