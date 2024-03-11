#pragma once

#include <meojson/json.hpp>
#include <type_traits>

namespace lhg::schema
{

template <typename T>
concept arithmetic = std::is_arithmetic<T>::value;

#define __LHG_SCHEMA_ARI_ENTRY(name) \
    template <arithmetic T>          \
    Builder& name(T&& value)   \
    {                                \
        obj[#name] = value;          \
        return *this;                \
    }

#define __LHG_SCHEMA_INT_ENTRY(name) \
    template <std::integral T>       \
    Builder& name(T&& value)   \
    {                                \
        obj[#name] = value;          \
        return *this;                \
    }

#define __LHG_SCHEMA_STR_ENTRY(name)         \
    Builder& name(std::string&& value) \
    {                                        \
        obj[#name] = value;                  \
        return *this;                        \
    }

#define __LHG_SCHEMA_FLG_ENTRY(name) \
    Builder& name(bool value)  \
    {                                \
        obj[#name] = value;          \
        return *this;                \
    }

struct Builder
{
    json::object obj;

    Builder(const json::object& obj = {}) : obj(obj) {}

    __LHG_SCHEMA_STR_ENTRY(title)

    __LHG_SCHEMA_ARI_ENTRY(multipleOf)

    __LHG_SCHEMA_ARI_ENTRY(maximum)
    __LHG_SCHEMA_ARI_ENTRY(exclusiveMaximum)
    __LHG_SCHEMA_ARI_ENTRY(minimum)
    __LHG_SCHEMA_ARI_ENTRY(exclusiveMinimum)

    __LHG_SCHEMA_INT_ENTRY(maxLength)
    __LHG_SCHEMA_INT_ENTRY(minLength)

    __LHG_SCHEMA_STR_ENTRY(pattern)

    __LHG_SCHEMA_INT_ENTRY(maxItems)
    __LHG_SCHEMA_INT_ENTRY(minItems)

    __LHG_SCHEMA_FLG_ENTRY(uniqueItems)

    __LHG_SCHEMA_INT_ENTRY(maxProperties)
    __LHG_SCHEMA_INT_ENTRY(minProperties)

    template <typename T>
    Builder& required(T&& keys)
    {
        obj["required"] = std::vector<std::string>(std::forward<T>(keys));
        return *this;
    }

    template <typename T>
    Builder& enum_(T&& vals)
    {
        obj["enum"] = json::array(std::forward<T>(vals));
        return *this;
    }

    __LHG_SCHEMA_STR_ENTRY(type)

    template <typename T>
    Builder& allOf(T&& schs)
    {
        obj["allOf"] = std::vector<json::object>(std::forward<T>(schs));
        return *this;
    }

    template <typename T>
    Builder& oneOf(T&& schs)
    {
        obj["oneOf"] = std::vector<json::object>(std::forward<T>(schs));
        return *this;
    }

    template <typename T>
    Builder& anyOf(T&& schs)
    {
        obj["anyOf"] = std::vector<json::object>(std::forward<T>(schs));
        return *this;
    }

    Builder& not_(json::object&& sch)
    {
        obj["not"] = sch;
        return *this;
    }

    Builder& items(json::object&& sch)
    {
        obj["items"] = sch;
        return *this;
    }

    Builder& properties(json::object&& sch)
    {
        obj["properties"] = sch;
        return *this;
    }

    __LHG_SCHEMA_FLG_ENTRY(additionalProperties)
    Builder& additionalProperties(json::object&& sch)
    {
        obj["additionalProperties"] = sch;
        return *this;
    }

    __LHG_SCHEMA_STR_ENTRY(description)
    __LHG_SCHEMA_STR_ENTRY(format)

    Builder& default_(json::value&& val)
    {
        obj["default"] = val;
        return *this;
    }

    static json::object ref(std::string&& target) { return json::object { { "$ref", target } }; }
};

} // namespace lhg::schema
