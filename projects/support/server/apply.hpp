#pragma once

#include "function/call.hpp"
#include "server/dispatcher.hpp"

namespace lhg::server
{

namespace pri
{

    template <typename function_list, size_t index>
    inline void apply_function_impl(Dispatcher* dispatcher)
    {
        using func_tag = std::tuple_element_t<index, function_list>;
        dispatcher->handle(
            std::format("/api/{}", func_tag::name),
            [](auto& provider, auto& res, const auto& req) { call::call<func_tag>(provider, res, req); },
            [](auto& provider, auto& res) {});
    }

}

template <typename function_list>
inline void apply_function(Dispatcher* dispatcher)
{
    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (pri::apply_function_impl<function_list, I>(dispatcher), ...);
    }(std::make_index_sequence<std::tuple_size_v<function_list>> {});
}

}
