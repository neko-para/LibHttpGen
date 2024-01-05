#pragma once

#include <concepts>
#include <meojson/json.hpp>

namespace lhg
{

template <typename Type>
struct check_t
{
    static constexpr const bool enable = false;
};

template <typename Type>
struct schema_t
{
    static constexpr const char* const schema = "unknown";
};

template <typename Type>
struct schema_t<Type &&> : schema_t<Type> {};

template <typename Type>
bool check_var(json::value v) = delete;

#pragma region void

template <>
struct schema_t<void>
{
    static constexpr const char* const schema = "null";
};

#pragma endregion

#pragma region bool

template <>
struct check_t<bool>
{
    static constexpr const bool enable = true;
};

template <>
struct schema_t<bool>
{
    static constexpr const char* const schema = "boolean";
};

template <>
bool check_var<bool>(json::value v)
{
    return v.is_boolean();
}

#pragma endregion

#pragma region integral

template <std::integral Type>
struct check_t<Type>
{
    static constexpr const bool enable = true;
};

template <std::integral Type>
struct schema_t<Type>
{
    static constexpr const char* const schema = "number";
};

template <std::integral Type>
requires (!std::is_same_v<Type, bool>)
bool check_var(json::value v)
{
    return v.is_number();
}

#pragma endregion

#pragma region string

template <>
struct check_t<const char*>
{
    static constexpr const bool enable = true;
};

template <>
struct schema_t<const char*>
{
    static constexpr const char* const schema = "string";
};

template <>
bool check_var<const char*>(json::value v)
{
    return v.is_string();
}

#pragma endregion

} // namespace lhg
