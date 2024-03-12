#pragma once

#include <meojson/json.hpp>
#include <tuple>

#include "utils/type.hpp"

namespace lhg::call
{

enum class handle_oper
{
    invalid,
    normal,
    alloc,
    free
};

#pragma region handle

template <typename type, bool impl>
struct type_is_handle
{
    constexpr static bool value = false;
};

template <typename type>
struct type_is_handle<type, true>
{
    constexpr static bool value = type_is_handle<type, false>::value;
};

template <typename arg_tag, bool impl>
struct is_handle
{
    constexpr static bool value = type_is_handle<typename arg_tag::type, true>::value;
    constexpr static handle_oper oper =
        type_is_handle<typename arg_tag::type, true>::value ? handle_oper::normal : handle_oper::invalid;
};

template <typename arg_tag>
struct is_handle<arg_tag, true>
{
    constexpr static bool value = is_handle<arg_tag, false>::value;
    constexpr static handle_oper oper = is_handle<arg_tag, false>::oper;
};

template <typename arg_tag>
concept handle_arg = is_handle<arg_tag, true>::value;

#pragma endregion handle

#pragma region input

template <typename arg_tag, bool impl>
struct is_input
{
    constexpr static bool value = true;
};

template <typename arg_tag>
struct is_input<arg_tag, true>
{
    constexpr static bool value = is_input<arg_tag, false>::value;
};

#pragma endregion input

#pragma region output

template <typename arg_tag, bool impl>
struct is_output
{
    constexpr static bool value = false;
};

template <typename arg_tag>
struct is_output<arg_tag, true>
{
    constexpr static bool value = is_output<arg_tag, false>::value;
};

#pragma endregion output

#pragma region outer_state

template <typename type_, bool impl>
struct type_is_outer_state
{
    constexpr static bool value = false;
    using type = std::monostate;
};

template <typename type_>
struct type_is_outer_state<type_, true>
{
    constexpr static bool value = type_is_outer_state<type_, false>::value;
    using type = type_is_outer_state<type_, false>::type;
};

template <typename arg_tag, bool impl>
struct is_outer_state
{
    constexpr static bool value = type_is_outer_state<typename arg_tag::type, true>::value;
    using type = type_is_outer_state<typename arg_tag::type, true>::type;
};

template <typename arg_tag>
struct is_outer_state<arg_tag, true>
{
    constexpr static bool value = is_outer_state<arg_tag, false>::value;
    using type = is_outer_state<arg_tag, false>::type;
};

template <>
struct type_is_outer_state<const char*, false>
{
    constexpr static bool value = true;
    using type = std::string;
};

#pragma endregion outer_state

namespace pri
{

    template <typename arg_tag>
    struct get_arg_impl
    {
        using type = typename arg_tag::type;
    };

    template <typename arg_tag>
    using is_outer_state_impl = is_outer_state<arg_tag, true>;

}

template <typename arg_tuple>
using convert_arg_type = help::transform_tuple<arg_tuple, pri::get_arg_impl>;

template <typename arg_tuple>
using convert_outer_state = help::transform_tuple<arg_tuple, pri::is_outer_state_impl>;

} // namespace lhg::call