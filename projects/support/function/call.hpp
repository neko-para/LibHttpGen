#pragma once

#include "function/cast.hpp"
#include "function/interface.hpp"
#include "manager/manager.hpp"

namespace lhg::call
{

template <typename arg_tuple, size_t index, bool impl>
struct json_to_arg
{
    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static bool convert(ManagerProvider& provider, const json::object& req, call_arg_tuple& arg,
                        call_arg_state_tuple& state)
    {
        std::ignore = state;

        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        if constexpr (!is_input<arg_tag, true>::value) {
            return true;
        }

        auto name = arg_tag::name;
        if (!req.contains(name)) {
            return false;
        }

        const json::value& value = req.at(name);
        cast::from_json(provider, value, std::get<index>(arg), std::get<index>(state), arg_tag {});
        return true;
    }
};

template <typename arg_tuple, size_t index, bool impl>
struct arg_to_json
{
    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static void convert(ManagerProvider& provider, json::object& res, call_arg_tuple& arg, call_arg_state_tuple& state)
    {
        std::ignore = state;

        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        if constexpr (!is_output<arg_tag, true>::value) {
            return;
        }

        auto name = arg_tag::name;

        json::value value;
        cast::to_json(provider, value, std::get<index>(arg), std::get<index>(state), arg_tag {});

        res[name] = value;
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

    auto success = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (json_to_arg<arg_tuple, I, true>::convert(provider, req, arg, state) && ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple> - 1> {});

    if (!success) {
        return false;
    }

    auto param = help::runtime_remove_last(arg);
    auto ret = std::apply(func_ptr, std::move(param));

    std::get<std::tuple_size_v<call_arg_tuple> - 1>(arg) = ret;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (arg_to_json<arg_tuple, I, true>::convert(provider, res, arg, state), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    return true;
}

} // namespace lhg::call