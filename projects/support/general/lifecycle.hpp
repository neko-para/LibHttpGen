#pragma once

#include <meojson/json.hpp>
#include <tuple>
#include <type_traits>

#include "general/cast.hpp"
#include "general/traits.hpp"
#include "manager/callback_manager.hpp"
#include "manager/manager.hpp"
#include "utils/schema.hpp"

namespace lhg::lifecycle
{

template <typename arg_tuple, size_t index>
struct prepare_state
{
    using call_arg_tuple = traits::convert_arg_type<arg_tuple>;
    using call_state_tuple = traits::convert_outer_state<arg_tuple>;

    static void prepare(
        [[maybe_unused]] ManagerProvider& provider,
        [[maybe_unused]] const json::object& req,
        [[maybe_unused]] call_arg_tuple& arg,
        [[maybe_unused]] call_state_tuple& state)
    {
    }
};

template <typename callback_tag>
struct get_context
{
    using func_type = typename callback_tag::type;
    using arg_tuple = typename func_type::args;

    using call_arg_tuple = traits::convert_arg_type<arg_tuple>;

    static callback::context_info* get(const call_arg_tuple& arg)
    {
        return static_cast<callback::context_info*>(std::get<callback_tag::context>(arg));
    }
};

template <typename arg_tuple, size_t index, bool is_call>
struct json_to_arg
{
    using arg_tag = std::tuple_element_t<index, arg_tuple>;
    using call_arg_tuple = traits::convert_arg_type<arg_tuple>;
    using call_state_tuple = traits::convert_outer_state<arg_tuple>;

    static constexpr bool active =
        !std::is_same_v<typename arg_tag::type, void>
        && (is_call ? traits::is_input<arg_tag> : traits::is_output<arg_tag>);

    static bool convert(
        ManagerProvider& provider,
        const json::object& req,
        call_arg_tuple& arg,
        call_state_tuple& state)
    {
        if constexpr (!active) {
            return true;
        }
        else {
            auto name = arg_tag::name;
            if (!req.contains(name)) {
                return false;
            }
            const auto& value = req.at(name);
            cast::from_json(
                provider,
                value,
                std::get<index>(arg),
                std::get<index>(state),
                arg_tag {});
            return true;
        }
    }

    static void schema(json::object& res)
    {
        if constexpr (!active) {
            return;
        }
        else {
            using schema_info = traits::schema<typename arg_tag::type, arg_tag>;

            auto name = arg_tag::name;
            schema::Builder b;
            b.type(schema_info::value);
            if constexpr (schema_info::title) {
                b.title(schema_info::title);
            }
            res[name] = b.obj;
        }
    }
};

template <typename arg_tuple, size_t index, bool is_call>
struct arg_to_json
{
    using arg_tag = std::tuple_element_t<index, arg_tuple>;
    using call_arg_tuple = traits::convert_arg_type<arg_tuple>;
    using call_state_tuple = traits::convert_outer_state<arg_tuple>;

    static constexpr bool active =
        !std::is_same_v<typename arg_tag::type, void>
        && (is_call ? traits::is_output<arg_tag> : traits::is_input<arg_tag>);

    static void convert(
        ManagerProvider& provider,
        json::object& res,
        call_arg_tuple& arg,
        call_state_tuple& state)
    {
        if constexpr (!active) {
            return;
        }
        else {
            auto name = arg_tag::name;
            json::value value;

            cast::to_json(
                provider,
                value,
                std::get<index>(arg),
                std::get<index>(state),
                arg_tag {});

            res[name] = value;
        }
    }

    static void schema(json::object& res)
    {
        if constexpr (!active) {
            return;
        }
        else {
            using schema_info = traits::schema<typename arg_tag::type, arg_tag>;

            auto name = arg_tag::name;
            schema::Builder b;
            b.type(schema_info::value);
            if constexpr (schema_info::title) {
                b.title(schema_info::title);
            }
            res[name] = b.obj;
        }
    }
};

}
