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
struct from_json_fix_t
{
    using from_t = Type;
};

template <>
struct from_json_fix_t<const char*>
{
    using from_t = std::string;
};

template <typename Type>
typename from_json_fix_t<Type>::from_t from_json(json::value v) LHG_NOT_IMPL_FUNC;

template <typename Type>
inline Type from_json_fix(typename from_json_fix_t<Type>::from_t& v)
{
    return v;
}

template <typename Type>
json::value to_json(Type v) LHG_NOT_IMPL_FUNC;

// from_json

template <json_value_can_as Type>
inline Type from_json(json::value v)
{
    return v.as<Type>();
}

template <>
inline std::string from_json<const char*>(json::value v)
{
    return v.as_string();
}

// from_json_fix

template <>
inline const char* from_json_fix<const char*>(std::string& v)
{
    return v.c_str();
}

// to_json

template <can_construct_json_value Type>
inline json::value to_json(Type v)
{
    return json::value(v);
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
