#pragma once

#include <meojson/json.hpp>
#include <tuple>

#include "utils/type.hpp"

namespace lhg
{

enum class handle_oper
{
    invalid,
    normal,
    alloc,
    free,
    scope
};

template <typename arg_tag, bool impl>
struct is_handle
{
    constexpr static bool value = false;
    constexpr static handle_oper oper = handle_oper::invalid;
};

template <typename arg_tag, bool impl>
struct is_input
{
    constexpr static bool value = true;
    using type = typename arg_tag::type;
};

template <typename arg_tag, bool impl>
struct is_output
{
    constexpr static bool value = false;
    using type = std::monostate;
};

template <typename arg_tag, bool impl>
struct is_outer_state
{
    constexpr static bool value = false;
    using type = std::monostate;
};

namespace pri
{

    template <typename arg_tag>
    struct get_arg_impl
    {
        using type = typename arg_tag::type;
    };

    template <typename arg_tag>
    using is_input_impl = lhg::is_input<arg_tag, true>;

    template <typename arg_tag>
    using is_output_impl = lhg::is_output<arg_tag, true>;

    template <typename arg_tag>
    using is_outer_state_impl = lhg::is_outer_state<arg_tag, true>;

}

template <typename arg_tuple>
using convert_arg_type = help::transform_tuple<arg_tuple, pri::get_arg_impl>;

// template <typename arg_tuple>
// using get_ret = std::tuple_element_t<std::tuple_size_v<arg_tuple> - 1, arg_tuple>;

// template <typename arg_tuple>
// using convert_ret = get_ret<arg_tuple>::type;

template <typename arg_tuple>
using convert_input = help::transform_tuple<arg_tuple, pri::is_input_impl>;

template <typename arg_tuple>
using convert_output = help::transform_tuple<arg_tuple, pri::is_output_impl>;

template <typename arg_tuple>
using convert_outer_state = help::transform_tuple<arg_tuple, pri::is_outer_state_impl>;

}
