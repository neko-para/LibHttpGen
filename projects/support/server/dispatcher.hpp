#pragma once

#include <algorithm>
#include <format>
#include <iterator>
#include <meojson/json.hpp>

#include "manager/manager.hpp"
#include "server/context.hpp"
#include "server/url.hpp"
#include "utils/boost.hpp"
#include "utils/schema.hpp"

namespace lhg::server
{

struct Endpoint
{
    std::function<void(ManagerProvider& provider, json::object& res, const json::object& req)>
        process = nullptr;
    std::function<void(json::object& req, json::object& res)> schema = nullptr;

    Endpoint() = default;
    template <typename F1, typename F2>
    Endpoint(F1&& f1, F2&& f2)
        : process(std::forward<F1>(f1))
        , schema(std::forward<F2>(f2))
    {
    }
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

    void setup_help(std::string route, std::string title, std::string version)
    {
        json::object _info = { { "title", title }, { "version", version } };
        handle(
            route,
            [this, info = std::move(_info)](auto& provider, auto& res, const auto& req) {
                if (help.has_value()) {
                    res = help.value();
                }
                else {
                    json::object paths;

                    auto enumerate =
                        [&](const auto& self, const Node* current, std::string curp) -> void {
                        if (current->endpoint) {
                            std::string operIdWithSlash = curp == "" ? "_" : curp;
                            std::string operId;
                            std::transform(
                                operIdWithSlash.begin(),
                                operIdWithSlash.end(),
                                std::back_insert_iterator<std::string>(operId),
                                [](char ch) { return ch != '/' ? ch : '_'; });

                            json::object req, res;
                            current->endpoint->schema(req, res);

                            paths[curp == "" ? "/" : curp] = {
                                { "post",
                                  { { "operationId", operId },
                                    { "requestBody",
                                      { { "content",
                                          { { "application/json", { { "schema", req } } } } } } },
                                    { "responses",
                                      { { "200",
                                          { { "content",
                                              { { "application/json",
                                                  { { "schema", res } } } } } } } } } } }
                            };
                        }

                        for (const auto& [sub, subnode] : current->child) {
                            self(self, &subnode, curp + '/' + sub);
                        }
                    };
                    enumerate(enumerate, &root, "");

                    res = { { "openapi", "3.0.0" }, { "info", info }, { "paths", paths } };
                    help = res;
                }
            },
            [](auto& req, auto& res) {
                req = {};
                res = schema::Builder().type("object").obj;
            });
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
            json::object req_obj =
                json::parse(ctx.req_.body()).value_or(json::object {}).as_object();
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
    std::optional<json::object> help;
};

} // namespace lhg::server
