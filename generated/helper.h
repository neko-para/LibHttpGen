#include <concepts>
#include <meojson/json.hpp>
#include <optional>
#include <string>
#include <tuple>

#include "Handle/Context.hpp"
#include "Helper/CallbackManager.hpp"
#include "Helper/HandleManager.hpp"
#include "Helper/UrlSegments.hpp"

#ifdef LHG_DELETE_NOT_IMPL
#define LHG_NOT_IMPL_FUNC = delete
#else
#define LHG_NOT_IMPL_FUNC            \
    {                                \
        throw "not implemented yet"; \
    }
#endif

template <typename Type>
concept json_value_can_as = requires(json::value v) { static_cast<Type>(v); };

template <typename Type>
concept can_construct_json_value = requires(Type t) {
    {
        json::value(std::forward<Type>(t))
    } -> std::same_as<json::value>;
};

template <typename Type>
struct check_var_t : std::false_type
{};

template <typename Type>
struct schema_t
{
    static constexpr const char* schema = "unknown";
};

template <typename Type>
struct from_json_fix_t
{
    using from_t = Type;
};

template <typename Type>
bool check_var(json::value v) LHG_NOT_IMPL_FUNC;

template <typename Type>
typename from_json_fix_t<Type>::from_t from_json(json::value v) LHG_NOT_IMPL_FUNC;

template <typename Type>
inline Type from_json_fix(typename from_json_fix_t<Type>::from_t& v)
{
    return v;
}

template <typename Type>
json::value to_json(Type v) LHG_NOT_IMPL_FUNC;

template <json_value_can_as Type>
inline Type from_json(json::value v)
{
    return v.as<Type>();
}

template <can_construct_json_value Type>
inline json::value to_json(Type v)
{
    return json::value(v);
}

template <typename Type>
Type output_prepare() LHG_NOT_IMPL_FUNC;

template <typename Type>
json::value output_finalize(Type v) LHG_NOT_IMPL_FUNC;

// checks

template <>
struct schema_t<void>
{
    static constexpr const char* schema = "never";
};

template <std::integral Type>
struct check_var_t<Type> : std::true_type
{};

template <std::integral Type>
bool check_var(json::value v)
{
    return v.is_number();
}

template <std::integral Type>
struct schema_t<Type>
{
    static constexpr const char* schema = "number";
};

template <>
struct check_var_t<const char*> : std::true_type
{};

template <>
bool check_var<const char*>(json::value v)
{
    return v.is_string();
}

template <>
struct schema_t<const char*>
{
    static constexpr const char* schema = "string";
};

template <>
struct check_var_t<bool> : std::true_type
{};

template <>
bool check_var<bool>(json::value v)
{
    return v.is_boolean();
}

template <>
struct schema_t<bool>
{
    static constexpr const char* schema = "boolean";
};

// const char* <-> string

template <>
struct from_json_fix_t<const char*>
{
    using from_t = std::string;
};

template <>
inline std::string from_json<const char*>(json::value v)
{
    return v.as_string();
}

template <>
inline const char* from_json_fix<const char*>(std::string& v)
{
    return v.c_str();
}

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

template <typename F>
using callback_manager =
    callback_manager_helper<typename func_traits<F>::return_t, typename func_traits<F>::arguments_t>::type;

template <size_t C, typename F, typename... Args>
static typename func_traits<F>::return_t __CallbackImpl(Args... arg)
{
    using manager = callback_manager<F>;

    auto tuple_args = std::make_tuple(arg...);
    auto __ctx_ptr = reinterpret_cast<manager::CallbackContext*>(std::get<C>(tuple_args))->shared_from_this();
    std::string cid = __ctx_ptr->push(arg...);
    typename manager::CallbackContext::return_type result;
    __ctx_ptr->wait(cid, result);
    if constexpr (std::is_same_v<typename func_traits<F>::return_t, void>) {
        std::ignore = result;
    }
    else {
        return result;
    }
}

template <typename CM>
inline bool handle_callback(const char* name, CM& manager, Context& ctx, UrlSegments segs,
                            std::function<json::object(const typename CM::CallbackContext::args_type&)> convert)
{
    segs.reset();
    if (segs.enter_path(name)) {
        if (segs.enter_path("add")) {
            std::string id;
            manager.alloc(id);
            ctx.json_body({ { "id", id } });
            return true;
        }
        if (segs.enter_path("del")) {
            auto body = json::parse(ctx.req_.body());
            auto& obj = body.value().as_object();
            std::string id = obj["id"].as_string();
            manager.free(id);
            ctx.json_body({});
            return true;
        }
        std::string id;
        if (segs.enter_path("sub") && segs.enter_id(id)) {
            if (segs.enter_path("pull")) {
                auto __ctx = manager.find(id);
                std::vector<std::string> cids;
                __ctx->take(cids);
                json::array obj_ids;
                for (const auto& cid : cids) {
                    obj_ids.push_back(cid);
                }
                ctx.json_body({ { "ids", obj_ids } });
                return true;
            }
            if (segs.enter_path("ctx")) {
                std::string cid;
                if (segs.enter_id(cid)) {
                    if (segs.enter_path("request")) {
                        auto __inst_ctx = manager.find(id);
                        typename CM::CallbackContext::args_type args;
                        __inst_ctx->get_args(cid, args);
                        json::object __arg = convert(args);
                        ctx.json_body(__arg);
                        return true;
                    }
                    if (segs.enter_path("response")) {
                        auto __inst_ctx = manager.find(id);
                        __inst_ctx->resp(cid, 0);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
