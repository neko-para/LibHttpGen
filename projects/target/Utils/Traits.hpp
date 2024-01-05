#pragma once

namespace lhg
{

template <typename ArgTag>
struct is_callback
{
    static constexpr const bool value = false;
};

template <typename ArgTag>
struct is_callback_context
{
    static constexpr const bool value = false;
};

template <typename Type>
struct is_opaque
{
    static constexpr const bool value = false;
};

template <typename Type, typename FuncTag>
struct is_opaque_free
{
    static constexpr const bool value = false;
};

template <typename ArgTag>
struct is_output
{
    static constexpr const bool value = false;
};

template <typename ArgTag>
struct shown_in_schema
{
    static constexpr const bool value = true;
};

template <typename ArgTag>
struct arg_schema {};

template <typename ArgTag>
concept is_arg_schema_impl = requires {
    { arg_schema<ArgTag>::schema } -> std::same_as<const char* const&>;
};

template <typename FuncTag>
struct ret_schema {};

template <typename FuncTag>
concept is_ret_schema_impl = requires {
    { ret_schema<FuncTag>::schema } -> std::same_as<const char* const&>;
};

}
