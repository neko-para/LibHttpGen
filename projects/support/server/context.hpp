#pragma once

#include <format>
#include <meojson/json.hpp>

#include "utils/forward.hpp"

namespace lhg::server
{

struct Context
{
    Context(http::request<http::string_body>& req, http::response<http::string_body>& res)
        : req_(req)
        , res_(res)
    {
    }

    void json_body(const json::object& value)
    {
        res_.set(http::field::content_type, "application/json");
        res_.body() = value.to_string();
    }

    void internal_server_error(const std::string& why)
    {
        res_.result(http::status::internal_server_error);
        json_body({ { "error", why } });
    }

    void bad_request(const std::string& why)
    {
        res_.result(http::status::bad_request);
        json_body({ { "error", why } });
    }

    void not_found(const std::string& why)
    {
        res_.result(http::status::not_found);
        json_body({ { "error", why } });
    }

    void init()
    {
        res_.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res_.set(http::field::access_control_allow_origin, "*");
        res_.set(http::field::access_control_allow_headers, "Content-Type");
        res_.keep_alive(req_.keep_alive());
    }

    void match_verb()
    {
        bad_request(std::format("bad verb {}", std::string_view(req_.method_string())));
    }

    template <typename Func>
    void match_verb(http::verb v, Func func)
    {
        if (req_.method() == v) {
            func(*this);
        }
        else {
            match_verb();
        }
    }

    template <typename Func, typename... Args>
    void match_verb(http::verb v, Func func, Args&&... args)
    {
        if (req_.method() == v) {
            func(*this);
        }
        else {
            match_verb(std::forward(args...));
        }
    }

    http::request<http::string_body>& req_;
    http::response<http::string_body>& res_;
};

} // namespace lhg::server
