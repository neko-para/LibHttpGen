#pragma once

namespace lhg
{

template <typename Tuple, template <typename> class Transformer, typename Seq>
struct transform_tuple_impl;

template <typename... Types, template <typename> class Transformer, std::size_t... I>
struct transform_tuple_impl<std::tuple<Types...>, Transformer, std::index_sequence<I...>> {
    using type = std::tuple<typename Transformer<Types>::type...>;
};

template <typename Tuple, template <typename> class Transformer>
using transform_tuple = typename transform_tuple_impl<
    Tuple,
    Transformer,
    std::make_index_sequence<std::tuple_size_v<Tuple>>
>::type;

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

template <typename Type, typename FuncTag>
struct is_opaque_non_alloc
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
