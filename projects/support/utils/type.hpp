#pragma once

#include <tuple>

namespace lhg
{

namespace help
{

namespace pri
{

template <typename Tuple, template <typename> class Transformer, typename Seq>
struct transform_tuple_impl;

template <typename... Types, template <typename> class Transformer, std::size_t... I>
struct transform_tuple_impl<std::tuple<Types...>, Transformer, std::index_sequence<I...>>
{
    using type = std::tuple<typename Transformer<Types>::type...>;
};

template <typename T, std::size_t N>
struct remove_last_helper
{
    using type = decltype(std::tuple_cat(
        std::declval<typename remove_last_helper<T, N - 1>::type>(),
        std::declval<std::tuple<std::tuple_element_t<N - 1, T>>>()));
};

template <typename T>
struct remove_last_helper<T, 1>
{
    using type = std::tuple<>;
};

template <typename T>
struct remove_last
{
    static constexpr std::size_t size = std::tuple_size<T>::value;
    using type = typename remove_last_helper<T, size>::type;
};

template <typename Tuple, std::size_t... Indices>
inline auto runtime_remove_last_impl(Tuple&& t, std::index_sequence<Indices...>)
{
    return std::make_tuple(std::get<Indices>(std::forward<Tuple>(t))...);
}

}

template <typename Tuple, template <typename> class Transformer>
using transform_tuple = typename pri::transform_tuple_impl<
    Tuple,
    Transformer,
    std::make_index_sequence<std::tuple_size_v<Tuple>>>::type;

template <typename Tuple>
using remove_last_element = typename pri::remove_last<Tuple>::type;

template <typename... Args>
inline auto runtime_remove_last(const std::tuple<Args...>& t)
{
    return pri::runtime_remove_last_impl(t, std::make_index_sequence<sizeof...(Args) - 1> {});
}

template <typename T>
using last_element = typename std::tuple_element_t<std::tuple_size_v<T> - 1, T>;

}

}
