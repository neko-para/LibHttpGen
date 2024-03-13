#pragma once

#include "function/call.hpp"
#include "server/dispatcher.hpp"
#include "utils/schema.hpp"

namespace lhg::server
{

namespace pri
{

using S = schema::Builder;

template <typename function_list, size_t index>
inline void apply_function_impl(Dispatcher* dispatcher)
{
    using func_tag = std::tuple_element_t<index, function_list>;
    dispatcher->handle(
        std::format("/api/{}", func_tag::name),
        [](auto& provider, auto& res, const auto& req) {
            call::call<func_tag>(provider, res, req);
        },
        [](auto& req, auto& res) { call::get_schema<func_tag>(res, req); });
}

template <typename callback_list, size_t index>
inline void apply_callback_impl(Dispatcher* dispatcher)
{
    using cb_tag = std::tuple_element_t<index, callback_list>;
    using manager_type = CallbackManager<cb_tag>;

    dispatcher->handle(
        std::format("/callback/{}/new", cb_tag::name),
        [](auto& provider, auto& res, const auto& req) {
            std::string id;
            manager_type* manager = provider.get<manager_type, void>();

            manager->alloc(id, &provider);
            res["id"] = id;
        },
        [](auto& req, auto& res) {
            req = {};
            res = S().type("object").prop({ { "id", S().type("string").obj } }).obj;
        });

    dispatcher->handle(
        std::format("/callback/{}/free", cb_tag::name),
        [](auto& provider, auto& res, const auto& req) {
            std::string id = req.at("id").as_string();
            manager_type* manager = provider.get<manager_type, void>();

            manager->free(id, &provider);
        },
        [](auto& req, auto& res) {
            req = S().type("object").prop({ { "id", S().type("string").obj } }).obj;
            res = {};
        });

    dispatcher->handle(
        std::format("/callback/{}/query", cb_tag::name),
        [](auto& provider, auto& res, const auto& req) {
            std::string id = req.at("id").as_string();
            manager_type* manager = provider.get<manager_type, void>();
            std::vector<std::string> ids;

            auto ctx = manager->query(id);
            ctx->take_wait(ids);
            res["ids"] = ids;
        },
        [](auto& req, auto& res) {
            req = S().type("object").prop({ { "id", S().type("string").obj } }).obj;
            res = S().type("object")
                      .prop({ { "ids", S().type("array").items(S().type("string").obj).obj } })
                      .obj;
        });

    dispatcher->handle(
        std::format("/callback/{}/req", cb_tag::name),
        [](auto& provider, auto& res, const auto& req) {
            std::string id = req.at("id").as_string();
            std::string cid = req.at("cid").as_string();
            manager_type* manager = provider.get<manager_type, void>();
            json::object data;

            auto ctx = manager->query(id);
            ctx->get_req(cid, data);
            res["arg"] = data;
        },
        [](auto& req, auto& res) {
            req = S().type("object")
                      .prop({ { "id", S().type("string").obj }, { "cid", S().type("string").obj } })
                      .obj;
            // TODO: arg
            res = S().type("object").prop({ { "arg", S().obj } }).obj;
        });

    dispatcher->handle(
        std::format("/callback/{}/req", cb_tag::name),
        [](auto& provider, auto& res, const auto& req) {
            std::string id = req.at("id").as_string();
            std::string cid = req.at("cid").as_string();
            json::object data = req.at("ret").as_object();
            manager_type* manager = provider.get<manager_type, void>();

            auto ctx = manager->query(id);
            ctx->set_res(cid, data);
        },
        [](auto& req, auto& res) {
            // TODO: ret
            req = S().type("object")
                      .prop({ { "id", S().type("string").obj },
                              { "cid", S().type("string").obj },
                              { "ret", S().type("object").obj } })
                      .obj;
            res = {};
        });
}

}

template <typename function_list>
inline void apply_function(Dispatcher* dispatcher)
{
    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (pri::apply_function_impl<function_list, I>(dispatcher), ...);
    }(std::make_index_sequence<std::tuple_size_v<function_list>> {});
}

template <typename callback_list>
inline void apply_callback(Dispatcher* dispatcher)
{
    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (pri::apply_callback_impl<callback_list, I>(dispatcher), ...);
    }(std::make_index_sequence<std::tuple_size_v<callback_list>> {});
}

}
