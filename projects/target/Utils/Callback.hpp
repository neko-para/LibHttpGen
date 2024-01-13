#pragma once

#include <meojson/json.hpp>
#include <tuple>

#include "Handle/Context.hpp"
#include "Helper/CallbackManager.hpp"
#include "Helper/UrlSegments.hpp"

namespace lhg
{

template <typename T>
struct func_traits;

template <typename R, typename... Args>
struct func_traits<R (*)(Args...)>
{
    using return_t = R;
    using arguments_t = std::tuple<Args...>;
};

namespace __private
{

    template <typename Ret, typename Tuple, typename... Args>
    struct callback_manager_helper;

    template <typename Ret, typename... Args>
    struct callback_manager_helper<Ret, std::tuple<Args...>>
    {
        using type = CallbackManager<Ret, Args...>;
    };

}

template <typename F>
using callback_manager =
    __private::callback_manager_helper<typename func_traits<F>::return_t, typename func_traits<F>::arguments_t>::type;

template <size_t C, typename F, typename... Args>
static typename func_traits<F>::return_t callback_implementation(Args... arg)
{
    using manager = callback_manager<F>;

    auto tuple_args = std::make_tuple(arg...);
    auto __ctx_ptr = reinterpret_cast<manager::CallbackContext*>(std::get<C>(tuple_args))->shared_from_this();
    std::string cid = __ctx_ptr->push(arg...);
    typename manager::CallbackContext::return_type result;
    __ctx_ptr->wait(cid, result);
    if constexpr (!std::is_same_v<typename func_traits<F>::return_t, void>) {
        return result;
    }
}

template <size_t C, typename F, typename... Args>
struct get_callback_impl_helper
{
    static constexpr const F func = &callback_implementation<C, F, Args...>;
};

template <typename T, size_t C, typename F>
struct get_callback_impl;

template <size_t C, typename F, typename... Args>
struct get_callback_impl<std::tuple<Args...>, C, F>
{
    using type = get_callback_impl_helper<C, F, Args...>;
};

template <size_t C, typename F>
inline F get_callback()
{
    return get_callback_impl<typename func_traits<F>::arguments_t, C, F>::type::func;
}

template <typename CM>
inline bool handle_callback(
    const char* name, CM& manager, Context& ctx, UrlSegments segs, json::object& obj,
    std::function<json::object(const typename CM::CallbackContext::args_type&)> convert_arg,
    std::function<std::optional<typename CM::CallbackContext::return_type>(const json::value&)> convert_ret)
{
    segs.reset();
    if (segs.enter_path("callback")) {
        if (segs.enter_path(name)) {
            if (segs.enter_path("add")) {
                std::string id;
                manager.alloc(id);
                ctx.json_body({ { "data", { { "id", id } } } });
                return true;
            }
            else if (segs.enter_path("del")) {
                auto id = obj.find("id");
                if (!id.has_value()) {
                    ctx.json_body({ { "error", "id not provided" } });
                    return true;
                }
                if (!id.value().is_string()) {
                    ctx.json_body({ { "error", "id should be string" } });
                    return true;
                }
                if (manager.free(id.value().as_string())) {
                    ctx.json_body({ { "data", json::object {} } });
                }
                else {
                    ctx.json_body({ { "error", "id not found" } });
                }
                return true;
            }
            else if (segs.enter_path("pull")) {
                auto id = obj.find("id");
                if (!id.has_value()) {
                    ctx.json_body({ { "error", "id not provided" } });
                    return true;
                }
                if (!id.value().is_string()) {
                    ctx.json_body({ { "error", "id should be string" } });
                    return true;
                }
                auto __inst_ctx = manager.find(id.value().as_string());
                if (!__inst_ctx) {
                    ctx.json_body({ { "error", "id not found" } });
                    return true;
                }
                std::vector<std::string> cids;
                __inst_ctx->take(cids);
                json::array obj_ids;
                for (const auto& cid : cids) {
                    obj_ids.push_back(cid);
                }
                ctx.json_body({ { "data", { { "ids", obj_ids } } } });
                return true;
            }
            else if (segs.enter_path("request")) {
                auto id = obj.find("id");
                auto cid = obj.find("cid");
                if (!id.has_value()) {
                    ctx.json_body({ { "error", "id not provided" } });
                    return true;
                }
                if (!cid.has_value()) {
                    ctx.json_body({ { "error", "cid not provided" } });
                    return true;
                }
                if (!id.value().is_string()) {
                    ctx.json_body({ { "error", "id should be string" } });
                    return true;
                }
                if (!id.value().is_string()) {
                    ctx.json_body({ { "error", "cid should be string" } });
                    return true;
                }
                auto __inst_ctx = manager.find(id.value().as_string());
                if (!__inst_ctx) {
                    ctx.json_body({ { "error", "id not found" } });
                    return true;
                }
                typename CM::CallbackContext::args_type args;
                if (!__inst_ctx->get_args(cid.value().as_string(), args)) {
                    ctx.json_body({ { "error", "cid not found" } });
                    return true;
                }
                json::object __arg = convert_arg(args);
                ctx.json_body({ { "data", __arg } });
                return true;
            }
            else if (segs.enter_path("response")) {
                auto id = obj.find("id");
                auto cid = obj.find("cid");
                if (!id.has_value()) {
                    ctx.json_body({ { "error", "id not provided" } });
                    return true;
                }
                if (!cid.has_value()) {
                    ctx.json_body({ { "error", "cid not provided" } });
                    return true;
                }
                if (!id.value().is_string()) {
                    ctx.json_body({ { "error", "id should be string" } });
                    return true;
                }
                if (!id.value().is_string()) {
                    ctx.json_body({ { "error", "cid should be string" } });
                    return true;
                }
                auto __inst_ctx = manager.find(id.value().as_string());
                if (!__inst_ctx) {
                    ctx.json_body({ { "error", "id not found" } });
                    return true;
                }
                if constexpr (std::is_same_v<typename CM::CallbackContext::real_return_type, void>) {
                    if (!__inst_ctx->resp(cid.value().as_string(), 0)) {
                        ctx.json_body({ { "error", "cid not found" } });
                        return true;
                    }
                }
                else {
                    auto return_ = obj.find("return");
                    if (!return_.has_value()) {
                        ctx.json_body({ { "error", "return not provided" } });
                        return true;
                    }
                    auto ret = convert_ret(return_.value());
                    if (!ret.has_value()) {
                        ctx.json_body({ { "error", "return convert failed" } });
                        return true;
                    }
                    if (!__inst_ctx->resp(cid.value().as_string(), ret.value())) {
                        ctx.json_body({ { "data", json::object {} } });
                        return true;
                    }
                    else {
                        ctx.json_body({ { "error", "cid not found" } });
                        return true;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

} // namespace lhg
