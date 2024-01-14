#pragma once

#include <map>
#include <meojson/json.hpp>
#include <optional>
#include <variant>

#include "Handle/Context.hpp"
#include "Helper/UrlSegments.hpp"
#include "Utils/Callback.hpp"
#include "Utils/Check.hpp"
#include "Utils/Convert.hpp"
#include "Utils/Output.hpp"
#include "Utils/Traits.hpp"
#include "Utils/TypeHelp.hpp"

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

inline json::array keys_of(const json::object& obj)
{
    json::array keys;
    for (const auto& [k, v] : obj) {
        keys.push_back(k);
    }
    return keys;
}

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

inline json::object wrap_oper(const json::object& input, const json::object& output)
{
    return json::object {
        { "post",
          { { "responses", { { "200", { { "content", { { "application/json", { { "schema", output } } } } } } } } },
            { "requestBody", { { "content", { { "application/json", { { "schema", input } } } } } } } } }
    };
}

inline void help_api(json::object& result, const api_info_map& wrappers)
{
    for (const auto& [api, info] : wrappers) {
        auto input = info.input();
        auto output = info.output();
        result["/api/" + api] = wrap_oper(input, output);
    }
}

template <typename ArgTag>
inline void input_helper_entry(json::object& obj, ArgTag)
{
    if constexpr (!shown_in_schema<ArgTag>::value) {
        return;
    }
    if constexpr (is_arg_schema_impl<ArgTag>) {
        obj[ArgTag::name] = json::parse(arg_schema<ArgTag>::schema).value();
    }
    else if constexpr (is_callback<ArgTag>::value) {
        obj[ArgTag::name] = json::object { { "type", "string" }, { "title", is_callback<ArgTag>::name } };
    }
    else if constexpr (is_callback_context<ArgTag>::value) {
        return;
    }
    else {
        obj[ArgTag::name] = json::parse(schema_t<typename ArgTag::type>::schema).value();
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

        return { { "type", "object" }, { "properties", obj }, { "required", keys_of(obj) } };
    }
}

template <typename ArgTag>
inline void output_helper_entry(json::object& obj, ArgTag)
{
    if constexpr (!shown_in_schema<ArgTag>::value) {
        return;
    }
    if constexpr (is_output<ArgTag>::value) {
        obj[ArgTag::name] = json::parse(schema_t<typename ArgTag::type>::schema).value();
    }
}

json::object wrap_data_error(const json::object& data);

template <typename FuncTag>
inline json::object output_helper()
{
    using ArgTuple = typename FuncTag::arguments_t;
    using Return = typename FuncTag::return_t;

    json::object obj = { { "return", json::parse(schema_t<Return>::schema).value() } };
    if constexpr (is_ret_schema_impl<FuncTag>) {
        obj = { { "return", json::parse(ret_schema<FuncTag>::schema).value() } };
    }
    if constexpr (!std::is_same_v<ArgTuple, void>) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (output_helper_entry<std::tuple_element_t<I, ArgTuple>>(obj, {}), ...);
        }(std::make_index_sequence<std::tuple_size_v<ArgTuple>> {});
    }

    return wrap_data_error({ { "type", "object" }, { "properties", obj }, { "required", keys_of(obj) } });
}

template <typename ArgTag>
inline bool perform_check_entry(json::object& __param, std::string& __error)
{
    using Argt = typename ArgTag::type;

    if constexpr (is_callback_context<ArgTag>::value) {
        if (!check_var<const char*>(__param[ArgTag::name])) {
            __error = std::string(ArgTag::name) + " type error, expect string@" +
                      is_callback<typename is_callback_context<ArgTag>::callback_arg_tag>::name;
            return false;
        }
    }
    else if constexpr (is_callback<ArgTag>::value) {
        return true;
    }
    else if constexpr (is_opaque<Argt>::value) {
        if (!check_var<const char*>(__param[ArgTag::name])) {
            __error = std::string(ArgTag::name) + " type error, expect string@" + is_opaque<Argt>::name;
            return false;
        }
    }
    else if constexpr (is_output<ArgTag>::value) {
        return true;
    }
    else {
        if constexpr (check_t<Argt>::enable) {
            if (!check_var<Argt>(__param[ArgTag::name])) {
                __error = std::string(ArgTag::name) + " type error " + typeid(Argt).name();
                return false;
            }
        }
    }
    return true;
}

template <typename FuncTag>
inline bool perform_check(json::object& __param, std::string& __error)
{
    using ArgTuple = typename FuncTag::arguments_t;

    if constexpr (std::is_same_v<ArgTuple, void>) {
        return true;
    }
    else {
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
            return (perform_check_entry<std::tuple_element_t<I, ArgTuple>>(__param, __error) && ...);
        }(std::make_index_sequence<std::tuple_size_v<ArgTuple>> {});
    }
}

template <typename ArgTag>
struct temp_arg_t
{
    using type = from_json_fix_t<typename ArgTag::type>::type;
};

template <typename ArgTag>
struct call_arg_t
{
    using type = ArgTag::type;
};

template <typename ArgTag>
requires is_callback_context<ArgTag>::value || is_callback<ArgTag>::value || is_opaque<typename ArgTag::type>::value ||
         is_output<ArgTag>::value
struct temp_arg_t<ArgTag>
{
    using type = std::monostate;
};

template <typename FuncTag>
struct arg_set
{
    using temp_type = help::transform_tuple<typename FuncTag::arguments_t, temp_arg_t>;
    using call_type = help::transform_tuple<typename FuncTag::arguments_t, call_arg_t>;
};

template <typename FuncTag>
requires std::same_as<typename FuncTag::arguments_t, void>
struct arg_set<FuncTag>
{
    using temp_type = std::tuple<std::monostate>;
    using call_type = std::tuple<std::monostate>;
};

template <typename FuncTag, typename ArgTag>
bool perform_input_entry(typename arg_set<FuncTag>::temp_type& temp_data, json::object __param, std::string& __error)
{
    if constexpr (!std::is_same_v<typename temp_arg_t<ArgTag>::type, std::monostate>) {
        std::get<ArgTag::index>(temp_data) = from_json<typename ArgTag::type>(__param[ArgTag::name]);
    }
    return true;
}

template <typename FuncTag>
inline bool perform_input(typename arg_set<FuncTag>::temp_type& temp_data, json::object& __param, std::string& __error)
{
    using ArgTuple = typename FuncTag::arguments_t;

    if constexpr (std::is_same_v<ArgTuple, void>) {
        return true;
    }
    else {
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
            return (perform_input_entry<FuncTag, std::tuple_element_t<I, ArgTuple>>(temp_data, __param, __error) &&
                    ...);
        }(std::make_index_sequence<std::tuple_size_v<ArgTuple>> {});
    }
}

template <typename FuncTag, typename ArgTag>
bool perform_input_fix_entry(typename arg_set<FuncTag>::call_type& data,
                             typename arg_set<FuncTag>::temp_type& temp_data, json::object __param,
                             std::string& __error)
{
    auto& var = std::get<ArgTag::index>(data);
    if constexpr (!std::is_same_v<typename temp_arg_t<ArgTag>::type, std::monostate>) {
        var = from_json_fix<typename ArgTag::type>(std::get<ArgTag::index>(temp_data));
    }
    else if constexpr (is_callback<ArgTag>::value) {
        var = get_callback<is_callback<ArgTag>::context, typename ArgTag::type>();
    }
    else if constexpr (is_callback_context<ArgTag>::value) {
        using cb_arg = typename is_callback_context<ArgTag>::callback_arg_tag;
        auto& manager = is_callback<cb_arg>::manager;
        std::string id = __param[cb_arg::name].as_string();
        void* ctx = manager.find(id).get();
        if (!ctx) {
            __error = std::string(cb_arg::name) + " not found in manager";
            return false;
        }
        var = ctx;
    }
    else if constexpr (is_opaque<typename ArgTag::type>::value) {
        auto& manager = is_opaque<typename ArgTag::type>::manager;
        std::string id = __param[ArgTag::name].as_string();
        if constexpr (is_opaque_free<typename ArgTag::type, FuncTag>::value) {
            typename ArgTag::type handle = nullptr;
            if (!manager.del(id, handle)) {
                __error = std::string(ArgTag::name) + " not found in manager";
                return false;
            }
            var = handle;
        }
        else {
            typename ArgTag::type handle = manager.get(id);
            if (!handle) {
                __error = std::string(ArgTag::name) + " not found in manager";
                return false;
            }
            var = handle;
        }
    }
    else if constexpr (is_output<ArgTag>::value) {
        var = output_prepare<typename ArgTag::type>();
    }
    return true;
}

template <typename FuncTag>
inline bool perform_input_fix(typename arg_set<FuncTag>::call_type& data,
                              typename arg_set<FuncTag>::temp_type& temp_data, json::object& __param,
                              std::string& __error)
{
    using ArgTuple = typename FuncTag::arguments_t;

    if constexpr (std::is_same_v<ArgTuple, void>) {
        return true;
    }
    else {
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
            return (perform_input_fix_entry<FuncTag, std::tuple_element_t<I, ArgTuple>>(data, temp_data, __param,
                                                                                        __error) &&
                    ...);
        }(std::make_index_sequence<std::tuple_size_v<ArgTuple>> {});
    }
}

template <typename FuncTag, typename ArgTag>
void perform_output_entry(typename arg_set<FuncTag>::call_type& data, json::object& obj)
{
    if constexpr (is_output<ArgTag>::value) {
        obj[ArgTag::name] = output_finalize<typename ArgTag::type>(std::get<ArgTag::index>(data));
    }
}

template <typename FuncTag, typename RealReturn>
inline json::object perform_output(typename arg_set<FuncTag>::call_type& data, RealReturn ret)
{
    using ArgTuple = typename FuncTag::arguments_t;
    using Return = typename FuncTag::return_t;

    json::object obj;
    if constexpr (std::is_same_v<Return, void>) {
        obj["return"] = json::value(json::value::value_type::null);
    }
    else if constexpr (is_opaque<RealReturn>::value) {
        auto& manager = is_opaque<RealReturn>::manager;
        if constexpr (is_opaque_non_alloc<RealReturn, FuncTag>::value) {
            obj["return"] = manager.find(ret);
        }
        else {
            obj["return"] = manager.add(ret);
        }
    }
    else {
        obj["return"] = to_json(ret);
    }
    if constexpr (!std::is_same_v<ArgTuple, void>) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (perform_output_entry<FuncTag, std::tuple_element_t<I, ArgTuple>>(data, obj), ...);
        }(std::make_index_sequence<std::tuple_size_v<ArgTuple>> {});
    }
    return obj;
}

} // namespace lhg
