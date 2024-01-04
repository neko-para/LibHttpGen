#pragma once

#include <meojson/json.hpp>
#include <tuple>

#include "Handle/Context.hpp"
#include "Helper/CallbackManager.hpp"
#include "Helper/UrlSegments.hpp"

namespace lhg
{

namespace __private
{

    template <typename T>
    struct func_traits;

    template <typename R, typename... Args>
    struct func_traits<R (*)(Args...)>
    {
        using return_t = R;
        using arguments_t = std::tuple<Args...>;
    };

    template <typename Ret, typename Tuple, typename... Args>
    struct callback_manager_helper;

    template <typename Ret, typename... Args>
    struct callback_manager_helper<Ret, std::tuple<Args...>>
    {
        using type = CallbackManager<Ret, Args...>;
    };

}

template <typename F>
using callback_manager = __private::callback_manager_helper<typename __private::func_traits<F>::return_t,
                                                            typename __private::func_traits<F>::arguments_t>::type;

template <size_t C, typename F, typename... Args>
static typename __private::func_traits<F>::return_t callback_implementation(Args... arg)
{
    using manager = callback_manager<F>;

    auto tuple_args = std::make_tuple(arg...);
    auto __ctx_ptr = reinterpret_cast<manager::CallbackContext*>(std::get<C>(tuple_args))->shared_from_this();
    std::string cid = __ctx_ptr->push(arg...);
    typename manager::CallbackContext::return_type result;
    __ctx_ptr->wait(cid, result);
    if constexpr (!std::is_same_v<typename __private::func_traits<F>::return_t, void>) {
        return result;
    }
}

template <typename CM>
inline bool handle_callback(const char* name, CM& manager, Context& ctx, UrlSegments segs, json::object& obj,
                            std::function<json::object(const typename CM::CallbackContext::args_type&)> convert)
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
            std::string id;
            if (segs.enter_id(id)) {
                if (segs.enter_path("del")) {
                    if (manager.free(id)) {
                        ctx.json_body({ { "data", {} } });
                    }
                    else {
                        ctx.json_body({ { "error", "id not found" } });
                    }
                    return true;
                }
                else if (segs.enter_path("pull")) {
                    auto __inst_ctx = manager.find(id);
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
                std::string cid;
                if (segs.enter_id(cid)) {
                    if (segs.enter_path("request")) {
                        auto __inst_ctx = manager.find(id);
                        if (!__inst_ctx) {
                            ctx.json_body({ { "error", "id not found" } });
                            return true;
                        }
                        typename CM::CallbackContext::args_type args;
                        if (!__inst_ctx->get_args(cid, args)) {
                            ctx.json_body({ { "error", "cid not found" } });
                            return true;
                        }
                        json::object __arg = convert(args);
                        ctx.json_body({ { "data", __arg } });
                        return true;
                    }
                    else if (segs.enter_path("response")) {
                        auto __inst_ctx = manager.find(id);
                        if (!__inst_ctx) {
                            ctx.json_body({ { "error", "id not found" } });
                            return true;
                        }
                        if (!__inst_ctx->resp(cid, 0)) {
                            ctx.json_body({ { "error", "cid not found" } });
                            return true;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

} // namespace lhg
