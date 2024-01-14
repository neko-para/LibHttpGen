#pragma once

#include <functional>

#include "Utils/Api.hpp"

namespace lhg
{

inline json::object wrap_data_error(const json::object& data)
{
    return { { "type", "object" },
             { "oneOf",
               json::array { { { "properties", { { "data", data } } }, { "required", json::array { "data" } } },
                             { { "properties", { { "error", { { "type", "string" } } } } },
                               { "required", json::array { "error" } } } } } };
}

inline void help_callback(const char* name, json::object& result, const json::object& arg,
                          const std::optional<json::object>& ret)
{
    std::string prefix = std::string("/callback/") + name + "/";
    auto id_cid = json::object { { "id", { { "type", "string" } } }, { "cid", { { "type", "string" } } } };
    result[prefix + "dump"] = wrap_oper(
        {}, wrap_data_error(
                { { "type", "object" },
                  { "properties",
                    { { "ids", { { "type", "array" }, { "items", { { "type", "string" }, { "title", name } } } } } } },
                  { "required", json::array { "ids" } } }));
    result[prefix + "add"] = wrap_oper({}, wrap_data_error({ { "type", "object" },
                                                             { "properties", { { "id", { { "type", "string" } } } } },
                                                             { "required", json::array { "id" } } }));
    result[prefix + "del"] = wrap_oper({ { "type", "object" },
                                         { "properties", { { "id", { { "type", "string" } } } } },
                                         { "required", json::array { "id" } } },
                                       wrap_data_error({}));
    result[prefix + "pull"] =
        wrap_oper({ { "type", "object" },
                    { "properties", { { "id", { { "type", "string" } } } } },
                    { "required", json::array { "id" } } },
                  wrap_data_error(
                      { { "type", "object" },
                        { "properties", { { "ids", { { "type", "array" }, { "items", { { "type", "string" } } } } } } },
                        { "required", json::array { "ids" } } }));
    result[prefix + "request"] =
        wrap_oper({ { "type", "object" }, { "properties", id_cid }, { "required", json::array { "id", "cid" } } },
                  wrap_data_error({ { "type", "object" }, { "properties", arg }, { "required", keys_of(arg) } }));
    result[prefix + "response"] =
        wrap_oper({ { "type", "object" },
                    { "properties", ret.has_value() ? (id_cid | json::object { { "return", ret.value() } }) : id_cid },
                    { "required", json::array { "id", "cid" } } },
                  wrap_data_error({}));
}

inline bool handle_help(Context& ctx, UrlSegments segs, const api_info_map& wrappers,
                        const std::vector<std::string>& opaques, std::function<void(json::object&)> callbacks)
{
    segs.reset();
    if (segs.enter_path("help") && segs.end()) {
        json::object result;

        help_api(result, wrappers);

        for (const auto& opaque : opaques) {
            result["/opaque/" + opaque] = wrap_oper(
                {}, wrap_data_error({ { "type", "object" },
                                      { "additionalProperties", { { "type", "string" }, { "title", opaque } } } }));
        }

        callbacks(result);

        ctx.json_body(
            { { "openapi", "3.0" }, { "info", { { "title", "lhg" }, { "version", "1.0" } } }, { "paths", result } });
        return true;
    }
    return false;
}

}
