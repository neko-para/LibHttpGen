#pragma once

#include <format>
#include <meojson/json.hpp>

#include "manager/manager.hpp"
#include "server/context.hpp"
#include "server/url.hpp"
#include "utils/forward.hpp"

namespace lhg::server
{

struct Endpoint
{
    std::function<void(ManagerProvider& provider, json::object& res, const json::object& req)> process = nullptr;
    std::function<void(ManagerProvider& provider, json::object& res)> schema = nullptr;

    Endpoint() = default;
    template <typename F1, typename F2>
    Endpoint(F1&& f1, F2&& f2) : process(std::forward<F1>(f1)), schema(std::forward<F2>(f2))
    {}
};

class Dispatcher
{
public:
    template <typename... EndpointArgs>
    void handle(std::string route, EndpointArgs&&... endpoint)
    {
        auto segs = segment_split(route);

        Node* current = &root;

        for (const auto& seg : segs) {
            auto it = current->child.find(seg);
            if (it == current->child.end()) {
                it = current->child.emplace(seg, Node { {}, nullptr }).first;
            }
            current = &it->second;
        }

        current->endpoint = std::make_unique<Endpoint>(std::forward<EndpointArgs>(endpoint)...);
    }

private:
    friend class Session;

    http::message_generator handle_request(http::request<http::string_body>&& req)
    {
        http::response<http::string_body> res { http::status::ok, req.version() };

        std::string url = req.target();

        auto url_segs = segment_split(url);

        Node* current = &root;

        for (const auto& seg : url_segs) {
            auto it = current->child.find(seg);
            if (it != current->child.end()) {
                current = &it->second;
            }
            else {
                current = nullptr;
                break;
            }
        }

        Context ctx(req, res);
        ctx.init();

        if (current && current->endpoint) {
            json::object req_obj = json::parse(ctx.req_.body()).value_or(json::object {}).as_object();
            json::object res_obj;
            current->endpoint->process(provider, res_obj, req_obj);
            ctx.json_body(res_obj);
        }
        else {
            ctx.bad_request(std::format("unknown path {}", url));
        }

        res.prepare_payload();

        return res;
    }

    struct Node
    {
        std::map<std::string, Node> child;
        std::unique_ptr<Endpoint> endpoint;
    };

    ManagerProvider provider;
    Node root;
};

} // namespace lhg::server
