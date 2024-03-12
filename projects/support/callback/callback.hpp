#pragma once

#include "callback/cast.hpp"
#include "callback/interface.hpp"
#include "manager/manager.hpp"
#include <tuple>
#include <type_traits>
#include <variant>

namespace lhg::callback
{

using callback_processer = void (*)(json::object& res, const json::object& req, void* context);

struct context_info
{
    ManagerProvider* provider;
    callback_processer process;
    void* context; // used by callback manager
};

template <typename callback_tag, bool impl>
struct get_context
{
    using func_type = typename callback_tag::type;
    using arg_tuple = typename func_type::args;

    using call_arg_tuple = convert_arg_type<arg_tuple>;

    static context_info* get(const call_arg_tuple& arg)
    {
        return static_cast<context_info*>(std::get<callback_tag::context>(arg));
    }
};

template <typename callback_tag>
struct get_context<callback_tag, true>
{
    using func_type = typename callback_tag::type;
    using arg_tuple = typename func_type::args;

    using call_arg_tuple = convert_arg_type<arg_tuple>;

    static context_info* get(const call_arg_tuple& arg) { return get_context<callback_tag, false>::get(arg); }
};

template <typename arg_tuple, size_t index, bool impl>
struct json_to_arg
{
    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static bool convert(ManagerProvider& provider, const json::object& res, call_arg_tuple& arg,
                        call_arg_state_tuple& state)
    {
        std::ignore = state;

        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        if constexpr (!is_output<arg_tag, true>::value) {
            return true;
        }
        else if constexpr (std::is_same_v<typename arg_tag::type, void>) {
            return true;
        }
        else {
            auto name = arg_tag::name;
            if (!res.contains(name)) {
                return false;
            }

            const json::value& value = res.at(name);
            cast::from_json(provider, value, std::get<index>(arg), std::get<index>(state), arg_tag {});
            return true;
        }
    }
};

template <typename arg_tuple, size_t index, bool impl>
struct arg_to_json
{
    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static void convert(ManagerProvider& provider, json::object& req, call_arg_tuple& arg, call_arg_state_tuple& state)
    {
        std::ignore = state;

        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        if constexpr (!is_input<arg_tag, true>::value || std::is_same_v<typename arg_tag::type, void>) {
            return;
        }
        else {
            auto name = arg_tag::name;

            json::value value;
            cast::to_json(provider, value, std::get<index>(arg), std::get<index>(state), arg_tag {});

            req[name] = value;
        }
    }
};

template <typename callback_tag>
auto create_callback() -> callback_tag::func_type
{
    using func_type = typename callback_tag::type;
    using arg_tuple = typename func_type::args;

    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    return [](auto... real_arg) {
        call_arg_tuple arg(real_arg..., std::monostate {});
        call_arg_state_tuple state;

        context_info* context = get_context<callback_tag, true>::get(arg);

        json::object req, res;

        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (arg_to_json<arg_tuple, I, true>::convert(*context->provider, req, arg, state), ...);
        }(std::make_index_sequence<std::tuple_size_v<arg_tuple> - 1> {});

        context->process(res, req, context->context);

        bool success = [&]<std::size_t... I>(std::index_sequence<I...>) {
            return (json_to_arg<arg_tuple, I, true>::convert(*context->provider, res, arg, state) && ...);
        }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

        if (!success) {
            throw "callback error";
        }

        if constexpr (std::is_same_v<typename func_type::ret::type, void>) {
            ;
        }
        else {
            return std::get<func_type::ret::index>(arg);
        }
    };
}

} // namespace lhg::callback
