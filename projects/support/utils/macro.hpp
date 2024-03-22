#pragma once

#define LHGArgOuterState(arg_tag, _type)    \
    namespace lhg::traits                   \
    {                                       \
    template <>                             \
    struct is_outer_state<arg_tag>          \
    {                                       \
        constexpr static bool value = true; \
        using type = _type;                 \
    };                                      \
    }

#define LHGArgHandle(arg_tag, _oper)                            \
    namespace lhg::traits                                       \
    {                                                           \
    template <>                                                 \
    struct is_handle<arg_tag>                                   \
    {                                                           \
        constexpr static bool value = true;                     \
        constexpr static handle_oper oper = handle_oper::_oper; \
    };                                                          \
    }

#define LHGArgOutput(arg_tag)                        \
    namespace lhg::traits                            \
    {                                                \
    template <>                                      \
    inline constexpr bool is_input<arg_tag> = false; \
    template <>                                      \
    inline constexpr bool is_output<arg_tag> = true; \
    }

#define LHGArgHide(arg_tag)                           \
    namespace lhg::traits                             \
    {                                                 \
    template <>                                       \
    inline constexpr bool is_input<arg_tag> = false;  \
    template <>                                       \
    inline constexpr bool is_output<arg_tag> = false; \
    }

#define LHGArgPrepareStateBegin(func_tag, atag)                          \
    namespace lhg::lifecycle                                             \
    {                                                                    \
    template <>                                                          \
    struct prepare_state<typename func_tag::args, func_tag::atag::index> \
    {                                                                    \
        using arg_tuple = func_tag::args;                                \
        using arg_tag = func_tag::atag;                                  \
        using call_arg_tuple = traits::convert_arg_type<arg_tuple>;      \
        using call_state_tuple = traits::convert_outer_state<arg_tuple>; \
        static void prepare(                                             \
            [[maybe_unused]] ManagerProvider& provider,                  \
            [[maybe_unused]] const json::object& req,                    \
            [[maybe_unused]] call_arg_tuple& arg,                        \
            [[maybe_unused]] call_state_tuple& state)                    \
        {
#define LHGArgPrepareStateEnd() \
    }                           \
    }                           \
    ;                           \
    }

#define LHGArgGetContextBegin(cb_tag)                                 \
    namespace lhg::lifecycle                                          \
    {                                                                 \
    template <>                                                       \
    struct get_context<cb_tag>                                        \
    {                                                                 \
        using callback_tag = cb_tag;                                  \
        using func_type = typename callback_tag::type;                \
        using arg_tuple = typename func_type::args;                   \
        using call_arg_tuple = traits::convert_arg_type<arg_tuple>;   \
        static callback::context_info* get(const call_arg_tuple& arg) \
        {
#define LHGArgGetContextEnd() \
    }                         \
    }                         \
    ;                         \
    }

#define LHGArgFromJsonBegin(func_tag, atag, is_call)                               \
    namespace lhg::lifecycle                                                       \
    {                                                                              \
    template <>                                                                    \
    struct json_to_arg<typename func_tag::args, func_tag::atag::index, is_call>    \
    {                                                                              \
        using arg_tuple = func_tag::args;                                          \
        static constexpr size_t index = func_tag::atag::index;                     \
        using arg_tag = func_tag::atag;                                            \
        using call_arg_tuple = traits::convert_arg_type<arg_tuple>;                \
        using call_arg_state_tuple = traits::convert_outer_state<arg_tuple>;       \
                                                                                   \
        static constexpr bool active =                                             \
            !std::is_same_v<typename arg_tag::type, void>                          \
            && (is_call ? traits::is_input<arg_tag> : traits::is_output<arg_tag>); \
                                                                                   \
        static bool convert(                                                       \
            [[maybe_unused]] lhg::ManagerProvider& provider,                       \
            const json::object& req,                                               \
            [[maybe_unused]] call_arg_tuple& arg,                                  \
            [[maybe_unused]] call_arg_state_tuple& state)                          \
        {                                                                          \
            if constexpr (!active) {                                               \
                return true;                                                       \
            }                                                                      \
            else {                                                                 \
                auto name = arg_tag::name;                                         \
                if (!req.contains(name)) {                                         \
                    return false;                                                  \
                }                                                                  \
                json::value value = req.at(name);
#define LHGArgFromJsonMiddle()            \
    return true;                          \
    }                                     \
    }                                     \
    static void schema(json::object& res) \
    {                                     \
        if constexpr (!active) {          \
            return;                       \
        }                                 \
        else {                            \
            auto name = arg_tag::name;    \
            schema::Builder b;
#define LHGArgFromJsonEnd() \
    res[name] = b.obj;      \
    }                       \
    }                       \
    }                       \
    ;                       \
    }

#define LHGArgToJsonBegin(func_tag, atag, is_call)                                 \
    namespace lhg::lifecycle                                                       \
    {                                                                              \
    template <>                                                                    \
    struct arg_to_json<typename func_tag::args, func_tag::atag::index, is_call>    \
    {                                                                              \
        using arg_tuple = func_tag::args;                                          \
        static constexpr size_t index = func_tag::atag::index;                     \
        using arg_tag = func_tag::atag;                                            \
        using call_arg_tuple = traits::convert_arg_type<arg_tuple>;                \
        using call_arg_state_tuple = traits::convert_outer_state<arg_tuple>;       \
                                                                                   \
        static constexpr bool active =                                             \
            !std::is_same_v<typename arg_tag::type, void>                          \
            && (is_call ? traits::is_output<arg_tag> : traits::is_input<arg_tag>); \
                                                                                   \
        static void convert(                                                       \
            [[maybe_unused]] lhg::ManagerProvider& provider,                       \
            json::object& res,                                                     \
            [[maybe_unused]] call_arg_tuple& arg,                                  \
            [[maybe_unused]] call_arg_state_tuple& state)                          \
        {                                                                          \
            if constexpr (!active) {                                               \
                return;                                                            \
            }                                                                      \
            else {                                                                 \
                auto name = arg_tag::name;                                         \
                json::value value;
#define LHGArgToJsonMiddle()              \
    res[name] = value;                    \
    }                                     \
    }                                     \
    static void schema(json::object& res) \
    {                                     \
        if constexpr (!active) {          \
            return;                       \
        }                                 \
        else {                            \
            auto name = arg_tag::name;    \
            schema::Builder b;
#define LHGArgToJsonEnd() \
    res[name] = b.obj;    \
    }                     \
    }                     \
    }                     \
    ;                     \
    }
