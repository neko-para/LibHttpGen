#pragma once

#include "function/interface.hpp"
#include <tuple>
#include <type_traits>

namespace lhg
{

namespace cast
{

    template <typename type, typename state>
    inline void from_json(const json::value& j, type& v, state& s) = delete;

    template <std::integral type, typename state>
    inline void from_json(const json::value& j, type& v, state& s)
    {
        std::ignore = s;
        v = j.as<type>();
    }

    template <std::floating_point type, typename state>
    inline void from_json(const json::value& j, type& v, state& s)
    {
        std::ignore = s;
        v = j.as<type>();
    }

    template <typename state>
    inline void from_json(const json::value& j, bool& v, state& s)
    {
        std::ignore = s;
        v = j.as_boolean();
    }

    inline void from_json(const json::value& j, const char*& v, std::string& s)
    {
        s = j.as_string();
        v = s.c_str();
    }

    template <typename type, typename state>
    inline void to_json(json::value& j, const type& v, state& s) = delete;

    template <std::integral type, typename state>
    inline void to_json(json::value& j, const type& v, state& s)
    {
        std::ignore = s;
        j = v;
    }

    template <std::floating_point type, typename state>
    inline void to_json(json::value& j, const type& v, state& s)
    {
        std::ignore = s;
        j = v;
    }

    template <typename state>
    inline void to_json(json::value& j, const bool& v, state& s)
    {
        std::ignore = s;
        j = v;
    }

    template <typename state>
    inline void to_json(json::value& j, const char* const& v, state& s)
    {
        std::ignore = s;
        j = v;
    }

}

template <typename arg_tuple, size_t index, bool impl>
struct json_to_arg
{
    using call_arg_tuple = convert_input<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static bool convert(const json::object& req, call_arg_tuple& arg, call_arg_state_tuple& state)
    {
        std::ignore = state;

        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        auto name = arg_tag::name;
        if (!req.contains(name)) {
            return false;
        }

        const json::value& value = req.at(name);
        cast::from_json(value, std::get<index>(arg), std::get<index>(state));
        return true;
    }
};

template <typename arg_tuple, size_t index, bool impl>
struct arg_to_json
{
    using call_arg_tuple = convert_input<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    static void convert(json::object& res, call_arg_tuple& arg, call_arg_state_tuple& state)
    {
        std::ignore = state;

        using arg_tag = std::tuple_element_t<index, arg_tuple>;

        auto name = arg_tag::name;

        json::value value;
        cast::to_json(value, std::get<index>(arg), std::get<index>(state));

        res[name] = value;
    }
};

template <typename function_tag>
bool call(json::object& res, const json::object& req)
{
    constexpr auto func_ptr = function_tag::func;
    using func_type = typename function_tag::type;
    using arg_tuple = typename func_type::args;

    using call_arg_tuple = convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = convert_outer_state<arg_tuple>;

    call_arg_tuple arg;
    call_arg_state_tuple state;

    auto success = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (json_to_arg<arg_tuple, I, true>::convert(req, arg, state) && ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple> - 1> {});

    if (!success) {
        return false;
    }

    auto param = help::runtime_remove_last(arg);
    auto ret = std::apply(func_ptr, std::move(param));

    std::get<std::tuple_size_v<call_arg_tuple> - 1>(arg) = ret;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (arg_to_json<arg_tuple, I, true>::convert(res, arg, state), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    return true;
}

} // namespace lhg
