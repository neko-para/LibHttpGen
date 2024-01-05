#pragma once

#include <map>
#include <meojson/json.hpp>
#include <optional>

#include "Handle/Context.hpp"
#include "Helper/UrlSegments.hpp"
#include "Utils/Check.hpp"
#include "Utils/Traits.hpp"

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
        }
    }
    return false;
}

inline void help_api(json::object& result, const api_info_map& wrappers)
{
    for (const auto& [api, info] : wrappers) {
        auto input = info.input();
        auto output = info.output();
        result["/api/" + api] = json::object { { "body", input }, { "response", output } };
    }
}

template <typename ArgTag>
inline void input_helper_entry(json::object& obj, ArgTag)
{
    if constexpr (!shown_in_schema<ArgTag>::value) {
        return;
    }
    if constexpr (is_arg_schema_impl<ArgTag>) {
        obj[ArgTag::name] = arg_schema<ArgTag>::schema;
    }
    else if constexpr (is_callback<ArgTag>::value) {
        obj[ArgTag::name] = std::string("string@") + is_callback<ArgTag>::name;
    }
    else if constexpr (is_callback_context<ArgTag>::value) {
        return;
    }
    else {
        obj[ArgTag::name] = schema_t<typename ArgTag::type>::schema;
    }
}

template <typename FuncTag>
inline json::object input_helper()
{
    using ArgTuple = typename FuncTag::arguments_t;
    
    if constexpr (std::is_same_v<ArgTuple, void>) {
        return json::object {};
    }
    else {
        json::object obj;
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (input_helper_entry<std::tuple_element_t<I, ArgTuple>>(obj, {}), ...);
        }(std::make_index_sequence<std::tuple_size_v<ArgTuple>> {});

        return obj;
    }
}

template <typename ArgTag>
inline void output_helper_entry(json::object& obj, ArgTag)
{
    if constexpr (!shown_in_schema<ArgTag>::value) {
        return;
    }
    if constexpr (is_output<ArgTag>::value) {
        obj[ArgTag::name] = schema_t<typename ArgTag::type>::schema;
    }
}

template <typename FuncTag>
inline json::object output_helper()
{
    using ArgTuple = typename FuncTag::arguments_t;
    using Return = typename FuncTag::return_t;

    json::object obj = { { "return", schema_t<Return>::schema } };
    if constexpr (is_ret_schema_impl<FuncTag>) {
        obj = { { "return", ret_schema<FuncTag>::schema } };
    }
    if constexpr (!std::is_same_v<ArgTuple, void>) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (output_helper_entry<std::tuple_element_t<I, ArgTuple>>(obj, {}), ...);
        }(std::make_index_sequence<std::tuple_size_v<ArgTuple>> {});
    }

    return { { "data", obj }, { "error", "string" } };
}

} // namespace lhg
