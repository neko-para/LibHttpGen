#pragma once

#include "function/cast.hpp"
#include "function/interface.hpp"
#include "manager/manager.hpp"
#include "utils/schema.hpp"

namespace lhg::call
{

template <typename arg_tuple, size_t index, bool impl>
struct prepare_state
{
    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static void prepare(
        ManagerProvider& provider,
        const json::object& req,
        call_arg_tuple& arg,
        call_arg_state_tuple& state)
    {
        std::ignore = provider;
        std::ignore = req;
        std::ignore = arg;
        std::ignore = state;
    }
};

template <typename arg_tuple, size_t index, bool impl>
struct json_to_arg
{
    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static bool convert(
        ManagerProvider& provider,
        const json::object& req,
        call_arg_tuple& arg,
        call_arg_state_tuple& state)
    {
        std::ignore = state;

        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        if constexpr (!is_input<arg_tag, true>::value) {
            return true;
        }
        else {
            auto name = arg_tag::name;
            if (!req.contains(name)) {
                return false;
            }

            const json::value& value = req.at(name);
            cast::from_json(
                provider,
                value,
                std::get<index>(arg),
                std::get<index>(state),
                arg_tag {});
            return true;
        }
    }
};

template <typename arg_tuple, size_t index, bool impl>
struct json_to_arg_schema
{
    static void get(json::object& req)
    {
        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        if constexpr (!is_input<arg_tag, true>::value) {
            ;
        }
        else {
            auto name = arg_tag::name;
            schema::Builder b;
            b.type(cast::schema<arg_tag::type, arg_tag>::value);
            if constexpr (cast::schema<arg_tag::type, arg_tag>::title) {
                b.title(cast::schema<arg_tag::type, arg_tag>::title);
            }
            req[name] = b.obj;
        }
    }
};

template <typename arg_tuple, size_t index, bool impl>
struct arg_to_json
{
    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static void convert(
        ManagerProvider& provider,
        json::object& res,
        call_arg_tuple& arg,
        call_arg_state_tuple& state)
    {
        std::ignore = state;

        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        if constexpr (
            !is_output<arg_tag, true>::value || std::is_same_v<typename arg_tag::type, void>) {
            return;
        }
        else {
            auto name = arg_tag::name;

            json::value value;
            cast::to_json(
                provider,
                value,
                std::get<index>(arg),
                std::get<index>(state),
                arg_tag {});

            res[name] = value;
        }
    }
};

template <typename arg_tuple, size_t index, bool impl>
struct arg_to_json_schema
{
    static void get(json::object& res)
    {
        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        if constexpr (
            !is_output<arg_tag, true>::value || std::is_same_v<typename arg_tag::type, void>) {
            ;
        }
        else {
            auto name = arg_tag::name;
            schema::Builder b;
            b.type(cast::schema<arg_tag::type, arg_tag>::value);
            if constexpr (cast::schema<arg_tag::type, arg_tag>::title) {
                b.title(cast::schema<arg_tag::type, arg_tag>::title);
            }
            res[name] = b.obj;
        }
    }
};

template <typename function_tag>
bool call(ManagerProvider& provider, json::object& res, const json::object& req)
{
    constexpr auto func_ptr = function_tag::func;
    using func_type = typename function_tag::type;
    using arg_tuple = typename func_type::args;

    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    call_arg_tuple arg;
    call_arg_state_tuple state;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (prepare_state<arg_tuple, I, true>::prepare(provider, req, arg, state), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple> - 1> {});

    auto success = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (json_to_arg<arg_tuple, I, true>::convert(provider, req, arg, state) && ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple> - 1> {});

    if (!success) {
        return false;
    }

    auto param = help::runtime_remove_last(arg);
    if constexpr (std::is_same_v<typename func_type::ret::type, void>) {
        ;
    }
    else {
        auto ret = std::apply(func_ptr, std::move(param));
        std::get<std::tuple_size_v<call_arg_tuple> - 1>(arg) = ret;
    }

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (arg_to_json<arg_tuple, I, true>::convert(provider, res, arg, state), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    return true;
}

template <typename function_tag>
void get_schema(json::object& res, json::object& req)
{
    using func_type = typename function_tag::type;
    using arg_tuple = typename func_type::args;

    json::object req_prop, res_prop;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (json_to_arg_schema<arg_tuple, I, true>::get(req_prop), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (arg_to_json_schema<arg_tuple, I, true>::get(res_prop), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    res = schema::Builder().type("object").prop(res_prop).obj;
    req = schema::Builder().type("object").prop(req_prop).obj;
}

} // namespace lhg::call
