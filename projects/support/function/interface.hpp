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

template <typename arg_tuple>
using convert_input = help::transform_tuple<arg_tuple, is_input>;

template <typename arg_tuple>
using convert_output = help::transform_tuple<arg_tuple, is_output>;

}