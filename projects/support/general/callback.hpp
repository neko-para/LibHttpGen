
#pragma once

#include "general/lifecycle.hpp"
#include "general/traits.hpp"

namespace lhg::callback
{

template <typename callback_tag>
constexpr auto create_callback() -> callback_tag::func_type
{
    using func_type = typename callback_tag::type;
    using arg_tuple = typename func_type::args;

    using call_arg_tuple = traits::convert_arg_type<arg_tuple>;
    using call_arg_state_tuple = traits::convert_outer_state<arg_tuple>;

    return [](auto... real_arg) {
        // 此处不能直接使用 func_type::ret::type void在convert_arg_type时转化为了monostate
        call_arg_tuple arg(
            real_arg...,
            std::tuple_element_t<func_type::ret::index, call_arg_tuple> {});
        call_arg_state_tuple state;

        context_info* context = lifecycle::get_context<callback_tag>::get(arg);

        json::object req, res;

        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (lifecycle::arg_to_json<arg_tuple, I, false>::convert(
                 *context->provider,
                 req,
                 arg,
                 state),
             ...);
        }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

        auto try_convert = [&](const json::object& _res) {
            return [&]<std::size_t... I>(std::index_sequence<I...>) {
                return (
                    lifecycle::json_to_arg<arg_tuple, I, false>::convert(
                        *context->provider,
                        _res,
                        arg,
                        state)
                    && ...);
            }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});
        };

        context->process(res, req, try_convert);

        bool success = try_convert(res);

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

template <typename function_tag>
void get_schema_req(json::object& req)
{
    using func_type = typename function_tag::type;
    using arg_tuple = typename func_type::args;

    json::object req_prop;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (lifecycle::arg_to_json<arg_tuple, I, false>::schema(req_prop), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    req = schema::Builder().type("object").prop(req_prop).obj;
}

template <typename function_tag>
void get_schema_res(json::object& res)
{
    using func_type = typename function_tag::type;
    using arg_tuple = typename func_type::args;

    json::object res_prop;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (lifecycle::json_to_arg<arg_tuple, I, false>::schema(res_prop), ...);
    }(std::make_index_sequence<std::tuple_size_v<arg_tuple>> {});

    res = schema::Builder().type("object").prop(res_prop).obj;
}

}
