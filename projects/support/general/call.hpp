#pragma once

#include "general/lifecycle.hpp"
#include "general/traits.hpp"

namespace lhg::call
{

template <typename func_tag>
inline bool call(ManagerProvider& provider, json::object& res, const json::object& req)
{
    constexpr auto func_ptr = func_tag::func;

    using func_type = typename func_tag::type;
    using arg_tuple = typename func_type::args;

    using call_arg_tuple = traits::convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = traits::convert_outer_state<arg_tuple>;

    call_arg_tuple arg;
    call_arg_state_tuple state;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (lifecycle::prepare_state<arg_tuple, I>::prepare(provider, req, arg, state), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    auto success = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (
            lifecycle::json_to_arg<arg_tuple, I, true>::convert(provider, req, arg, state) && ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    if (!success) {
        return false;
    }

    auto param = help::runtime_remove_last(arg);
    if constexpr (std::is_same_v<typename func_type::ret::type, void>) {
        ;
    }
    else {
        auto ret = std::apply(func_ptr, std::move(param));
        std::get<func_type::ret::index>(arg) = ret;
    }

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (lifecycle::arg_to_json<arg_tuple, I, true>::convert(provider, res, arg, state), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    return true;
}

template <typename func_tag>
void get_schema(json::object& res, json::object& req)
{
    using func_type = typename func_tag::type;
    using arg_tuple = typename func_type::args;

    json::object req_prop, res_prop;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (lifecycle::json_to_arg<arg_tuple, I, true>::schema(req_prop), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (lifecycle::arg_to_json<arg_tuple, I, true>::schema(res_prop), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    res = schema::Builder().type("object").prop(res_prop).obj;
    req = schema::Builder().type("object").prop(req_prop).obj;
}

}
