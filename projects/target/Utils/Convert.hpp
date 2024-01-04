#pragma once

#include <meojson/json.hpp>

namespace lhg
{

template <typename Type>
concept can_convert_from_json = requires(json::value v) { static_cast<Type>(v); };

template <typename Type>
concept can_construct_json = requires(Type t) {
    {
        json::value(std::forward<Type>(t))
    } -> std::same_as<json::value>;
};

template <typename Type>
struct from_json_fix_t
{
    using type = Type;
};

template <typename Type>
typename from_json_fix_t<Type>::type from_json(json::value v) = delete;

template <typename Type>
inline Type from_json_fix(typename from_json_fix_t<Type>::type& v)
{
    return v;
}

template <typename Type>
json::value to_json(Type v) = delete;

#pragma region ConceptSpecialize

template <can_convert_from_json Type>
inline Type from_json(json::value v)
{
    return v.as<Type>();
}

template <can_construct_json Type>
inline json::value to_json(Type v)
{
    return json::value(v);
}

#pragma endregion

#pragma region string

template <>
struct from_json_fix_t<const char*>
{
    using type = std::string;
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

#pragma endregion

}
