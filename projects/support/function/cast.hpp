#pragma once

#include <meojson/json.hpp>

#include "manager/manager.hpp"
#include "manager/handle_manager.hpp"

namespace lhg::cast {

    template <typename type, typename state, typename arg_tag>
    inline void from_json(ManagerProvider& p, const json::value& j, type& v, state& s, arg_tag) = delete;

    template <std::integral type, typename state, typename arg_tag>
    inline void from_json(ManagerProvider& p, const json::value& j, type& v, state& s, arg_tag)
    {
        std::ignore = p;
        std::ignore = s;
        v = j.as<type>();
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

    template <handle_type type, typename state, typename arg_tag>
    inline void from_json(ManagerProvider& p, const json::value& j, type& v, state& s, arg_tag)
    {
        auto manager = p.get<HandleManager<type>, arg_tag>();
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

}
