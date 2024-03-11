#pragma once

#include <meojson/json.hpp>
#include <format>

#include "server/context.hpp"
#include "server/url.hpp"
#include "utils/forward.hpp"
#include "manager/manager.hpp"

namespace lhg::server
{

struct Endpoint
{
    std::function<void(ManagerProvider& provider, json::object& res, const json::object& req)> process;
    std::function<void(ManagerProvider& provider, json::object& res, json::object& req)> schema;
};

class Dispatcher
{
public:
    void handle(std::string route, Endpoint endpoint) {
        auto segs = segment_split(route);

        Node *current = &root;

        for (const auto& seg : segs) {
            auto it = current->child.find(seg);
            if (it == current->child.end()) {
                it = current->child.emplace(seg, Node {
                    {}, nullptr
                }).first;
            }
            current = &it->second;
        }

        current->endpoint = std::make_shared<Endpoint>(endpoint);
    }

private:
    friend class Session;

    http::message_generator handle_request(http::request<http::string_body>&& req)
    {
        http::response<http::string_body> res { http::status::ok, req.version() };

        std::string url = req.target();

        auto url_segs = segment_split(url);

        Node *current = &root;

        for (const auto& seg : url_segs) {
            auto it = current->child.find(seg);
            if (it != current->child.end()) {
                current = &it->second;
            } else {
                current = nullptr;
                break;
            }
        }

        Context ctx(req, res);
        ctx.init();

        if (current && current->endpoint) {
            json::object req = json::parse(ctx.req_.body()).value_or(json::object {}).as_object();
            json::object res;
            current->endpoint->process(provider, res, req);
            ctx.json_body(res);
        } else {
            ctx.bad_request(std::format("unknown path {}", url));
        }

        res.prepare_payload();

        return res;
    }

    struct Node
    {
        std::map<std::string, Node> child;
        std::shared_ptr<Endpoint> endpoint;
    };

    ManagerProvider provider;
    Node root;
};

}
