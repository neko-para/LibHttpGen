#pragma once

#include <variant>

#include "utils/type.hpp"

namespace lhg::traits
{

enum class handle_oper
{
    invalid,
    normal,

    // call only
    alloc,
    free,

    // callback only
    scope
};

template <typename type>
inline constexpr bool type_is_handle = false;

template <typename type>
inline const constexpr char* type_handle_name = nullptr;

template <typename arg_tag>
struct is_handle
{
    static constexpr bool value = type_is_handle<typename arg_tag::type>;
    static constexpr handle_oper oper =
        type_is_handle<typename arg_tag::type> ? handle_oper::normal : handle_oper::invalid;
};

template <typename arg_tag>
concept handle_arg_tag = is_handle<arg_tag>::value;

template <typename arg_tag>
inline constexpr bool is_input = true;

template <typename arg_tag>
inline constexpr bool is_output = false;

template <typename type_>
struct type_is_outer_state
{
    static constexpr bool value = false;
    using type = std::monostate;
};

template <typename arg_tag>
struct is_outer_state : public type_is_outer_state<typename arg_tag::type>
{
};

// spec

template <>
struct type_is_outer_state<const char*>
{
    static constexpr bool value = true;
    using type = std::string;
};

template <typename type, typename arg_tag>
struct schema
{
};

template <std::integral type, typename arg_tag>
struct schema<type, arg_tag>
{
    static const constexpr char* value = "number";
    static const constexpr char* title = nullptr;
};

template <std::floating_point type, typename arg_tag>
struct schema<type, arg_tag>
{
    static const constexpr char* value = "number";
    static const constexpr char* title = nullptr;
};

template <typename arg_tag>
struct schema<bool, arg_tag>
{
    static const constexpr char* value = "boolean";
    static const constexpr char* title = nullptr;
};

template <typename arg_tag>
struct schema<const char*, arg_tag>
{
    static const constexpr char* value = "string";
    static const constexpr char* title = nullptr;
};

template <typename type, traits::handle_arg_tag arg_tag>
struct schema<type, arg_tag>
{
    static const constexpr char* value = "string";
    static const constexpr char* title = traits::type_handle_name<type>;
};

namespace pri
{

template <typename arg_tag>
concept void_arg_tag = std::is_same_v<typename arg_tag::type, void>;

template <typename arg_tag>
struct get_arg_impl
{
    using type = typename arg_tag::type;
};

template <void_arg_tag arg_tag>
struct get_arg_impl<arg_tag>
{
    using type = std::monostate;
};

}

template <typename arg_tuple>
using convert_arg_type = help::transform_tuple<arg_tuple, pri::get_arg_impl>;

template <typename arg_tuple>
using convert_outer_state = help::transform_tuple<arg_tuple, is_outer_state>;

}
