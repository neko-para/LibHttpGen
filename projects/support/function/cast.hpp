#pragma once

#include <meojson/json.hpp>

#include "function/interface.hpp"
#include "manager/handle_manager.hpp"
#include "manager/manager.hpp"

namespace lhg::call::cast
{

template <typename type, typename state, typename arg_tag>
inline void from_json(ManagerProvider& p, const json::value& j, type& v, state& s, arg_tag) = delete;

template <std::integral type, typename state, typename arg_tag>
inline void from_json(ManagerProvider& p, const json::value& j, type& v, state& s, arg_tag)
{
    std::ignore = p;
    std::ignore = s;
    v = j.as<type>();
}

template <typename state, typename arg_tag>
inline void from_json(ManagerProvider& p, const json::value& j, unsigned char& v, state& s, arg_tag)
{
    std::ignore = p;
    std::ignore = s;
    v = static_cast<unsigned char>(j.as<unsigned>());
}

template <std::floating_point type, typename state, typename arg_tag>
inline void from_json(ManagerProvider& p, const json::value& j, type& v, state& s, arg_tag)
{
    std::ignore = p;
    std::ignore = s;
    v = j.as<type>();
}

template <typename state, typename arg_tag>
inline void from_json(ManagerProvider& p, const json::value& j, bool& v, state& s, arg_tag)
{
    std::ignore = p;
    std::ignore = s;
    v = j.as_boolean();
}

template <typename arg_tag>
inline void from_json(ManagerProvider& p, const json::value& j, const char*& v, std::string& s, arg_tag)
{
    std::ignore = p;
    s = j.as_string();
    v = s.c_str();
}

template <typename type, typename state, handle_arg arg_tag>
inline void from_json(ManagerProvider& p, const json::value& j, type& v, state& s, arg_tag)
{
    constexpr auto oper = is_handle<arg_tag, true>::oper;
    static_assert(oper != handle_oper::invalid, "from_json: invalid handle oper is not allowed");
    static_assert(oper != handle_oper::alloc, "from_json: alloc handle oper is not allowed");

    auto manager = p.get<HandleManager<type>, arg_tag>();

    if constexpr (oper == handle_oper::normal) {
        v = manager->get(j.as_string());
    }
    else if constexpr (oper == handle_oper::free) {
        manager->del(j.as_string(), v);
    }
}

template <typename type, typename state, typename arg_tag>
inline void to_json(ManagerProvider& p, json::value& j, const type& v, state& s, arg_tag) = delete;

template <std::integral type, typename state, typename arg_tag>
inline void to_json(ManagerProvider& p, json::value& j, const type& v, state& s, arg_tag)
{
    std::ignore = p;
    std::ignore = s;
    j = v;
}

template <std::floating_point type, typename state, typename arg_tag>
inline void to_json(ManagerProvider& p, json::value& j, const type& v, state& s, arg_tag)
{
    std::ignore = p;
    std::ignore = s;
    j = v;
}

template <typename state, typename arg_tag>
inline void to_json(ManagerProvider& p, json::value& j, const bool& v, state& s, arg_tag)
{
    std::ignore = p;
    std::ignore = s;
    j = v;
}

template <typename state, typename arg_tag>
inline void to_json(ManagerProvider& p, json::value& j, const char* const& v, state& s, arg_tag)
{
    std::ignore = p;
    std::ignore = s;
    j = v;
}

template <typename type, typename state, handle_arg arg_tag>
inline void to_json(ManagerProvider& p, json::value& j, const type& v, state& s, arg_tag)
{
    constexpr auto oper = is_handle<arg_tag, true>::oper;
    static_assert(oper != handle_oper::invalid, "to_json: invalid handle oper is not allowed");
    static_assert(oper != handle_oper::free, "to_json: free handle oper is not allowed");

    auto manager = p.get<HandleManager<type>, arg_tag>();

    if constexpr (oper == handle_oper::normal) {
        j = manager->find(v);
    }
    else if constexpr (oper == handle_oper::alloc) {
        j = manager->add(v);
    }
}

} // namespace lhg::call::cast
