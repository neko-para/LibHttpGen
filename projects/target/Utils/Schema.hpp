#pragma once

#include <array>
#include <meojson/json.hpp>
#include <regex>

namespace lhg
{

namespace json_schema
{
    inline bool is_integer(long double v)
    {
        return v == std::floor(v);
    }

    inline bool is_unique(const json::array& arr) {
        for (auto it1 = arr.begin(); it1 != arr.end(); it1++) {
            for (auto it2 = it1 + 1; it2 != arr.end(); it2++) {
                if (*it1 == *it2) {
                    return false;
                }
            }
        }
        return true;
    }

    bool validate(const json::value& schema, const json::value& value);

    inline auto validate_with(const json::value& schema)
    {
        return [&schema](const json::value& value) { return validate(schema, value); };
    }

    struct schema_error : std::exception
    {
        virtual const char* what() const noexcept override { return "json schema error"; }
    };

    inline bool check_type_entry(const std::string& type, const json::value& value)
    {
        if (type == "null") {
            return value.is_null();
        }
        else if (type == "boolean") {
            return value.is_boolean();
        }
        else if (type == "object") {
            return value.is_object();
        }
        else if (type == "array") {
            return value.is_array();
        }
        else if (type == "number") {
            return value.is_number();
        }
        else if (type == "string") {
            return value.is_string();
        }
        else if (type == "integer") {
            return value.is_number() && is_integer(value.as_long_double());
        }
        else {
            throw schema_error();
        }
    }

    inline bool check_type(const json::object& schema, const json::value& value)
    {
        auto type_opt = schema.find("type");
        if (!type_opt.has_value()) {
            return true;
        }
        const auto& type = type_opt.value();
        if (type.is_string()) {
            if (!check_type_entry(type.as_string(), value)) {
                return false;
            }
        }
        else if (type.is_array()) {
            if (!is_unique(type.as_array())) {
                throw schema_error();
            }
            for (const auto& v : type.as_array()) {
                if (!v.is_string()) {
                    throw schema_error();
                }
                if (!check_type_entry(v.as_string(), value)) {
                    return false;
                }
            }
        }
        else {
            throw schema_error();
        }
        return true;
    }

    inline bool check_enum(const json::object& schema, const json::value& value)
    {
        auto enum_opt = schema.find("enum");
        if (!enum_opt.has_value()) {
            return true;
        }
        const auto& enum_ = enum_opt.value();
        if (!enum_.is_array()) {
            throw schema_error();
        }
        for (const auto& v : enum_.as_array()) {
            if (v == value) {
                return true;
            }
        }
        return false;
    }

    inline bool check_const(const json::object& schema, const json::value& value)
    {
        auto const_opt = schema.find("const");
        if (!const_opt.has_value()) {
            return true;
        }
        return value == const_opt.value();
    }

    inline bool check_multipleOf(const json::object& schema, const json::value& value)
    {
        if (!value.is_number()) {
            return true;
        }
        auto value_num = value.as_long_double();

        auto multipleOf_opt = schema.find("multipleOf");
        if (!multipleOf_opt.has_value()) {
            return true;
        }
        const auto& multipleOf = multipleOf_opt.value();
        if (!multipleOf.is_number()) {
            throw schema_error();
        }
        auto multipleOf_num = multipleOf.as_long_double();
        if (multipleOf_num <= 0) {
            throw schema_error();
        }
        return is_integer(value_num / multipleOf_num);
    }

    inline bool check_maximum(const json::object& schema, const json::value& value)
    {
        if (!value.is_number()) {
            return true;
        }
        auto value_num = value.as_long_double();

        auto maximum_opt = schema.find("maximum");
        if (!maximum_opt.has_value()) {
            return true;
        }
        const auto& maximum = maximum_opt.value();
        if (!maximum.is_number()) {
            throw schema_error();
        }
        auto maximum_num = maximum.as_long_double();
        if (maximum_num <= 0) {
            throw schema_error();
        }
        return value_num <= maximum_num;
    }

    inline bool check_exclusiveMaximum(const json::object& schema, const json::value& value)
    {
        if (!value.is_number()) {
            return true;
        }
        auto value_num = value.as_long_double();

        auto exclusiveMaximum_opt = schema.find("exclusiveMaximum");
        if (!exclusiveMaximum_opt.has_value()) {
            return true;
        }
        const auto& exclusiveMaximum = exclusiveMaximum_opt.value();
        if (!exclusiveMaximum.is_number()) {
            throw schema_error();
        }
        auto exclusiveMaximum_num = exclusiveMaximum.as_long_double();
        if (exclusiveMaximum_num <= 0) {
            throw schema_error();
        }
        return value_num < exclusiveMaximum_num;
    }

    inline bool check_minimum(const json::object& schema, const json::value& value)
    {
        if (!value.is_number()) {
            return true;
        }
        auto value_num = value.as_long_double();

        auto minimum_opt = schema.find("minimum");
        if (!minimum_opt.has_value()) {
            return true;
        }
        const auto& minimum = minimum_opt.value();
        if (!minimum.is_number()) {
            throw schema_error();
        }
        auto minimum_num = minimum.as_long_double();
        if (minimum_num <= 0) {
            throw schema_error();
        }
        return value_num >= minimum_num;
    }

    inline bool check_exclusiveMinimum(const json::object& schema, const json::value& value)
    {
        if (!value.is_number()) {
            return true;
        }
        auto value_num = value.as_long_double();

        auto exclusiveMinimum_opt = schema.find("exclusiveMinimum");
        if (!exclusiveMinimum_opt.has_value()) {
            return true;
        }
        const auto& exclusiveMinimum = exclusiveMinimum_opt.value();
        if (!exclusiveMinimum.is_number()) {
            throw schema_error();
        }
        auto exclusiveMinimum_num = exclusiveMinimum.as_long_double();
        if (exclusiveMinimum_num <= 0) {
            throw schema_error();
        }
        return value_num > exclusiveMinimum_num;
    }

    inline bool check_maxLength(const json::object& schema, const json::value& value)
    {
        if (!value.is_string()) {
            return true;
        }
        auto value_str = value.as_string();

        auto maxLength_opt = schema.find("maxLength");
        if (!maxLength_opt.has_value()) {
            return true;
        }
        const auto& maxLength = maxLength_opt.value();
        if (!maxLength.is_number()) {
            throw schema_error();
        }
        return value_str.size() <= maxLength.as_unsigned();
    }

    inline bool check_minLength(const json::object& schema, const json::value& value)
    {
        if (!value.is_string()) {
            return true;
        }
        auto value_str = value.as_string();

        auto minLength_opt = schema.find("minLength");
        if (!minLength_opt.has_value()) {
            return true;
        }
        const auto& minLength = minLength_opt.value();
        if (!minLength.is_number()) {
            throw schema_error();
        }
        return value_str.size() >= minLength.as_unsigned();
    }

    inline bool check_pattern(const json::object& schema, const json::value& value)
    {
        if (!value.is_string()) {
            return true;
        }
        auto value_str = value.as_string();

        auto pattern_opt = schema.find("pattern");
        if (!pattern_opt.has_value()) {
            return true;
        }
        const auto& pattern = pattern_opt.value();
        if (!pattern.is_string()) {
            throw schema_error();
        }
        std::regex pattern_reg(pattern.as_string());
        return std::regex_match(value_str, pattern_reg);
    }

    inline bool check_items_additionalItems(const json::object& schema, const json::value& value)
    {
        if (!value.is_array()) {
            return true;
        }
        auto value_arr = value.as_array();

        auto items_opt = schema.find("items");
        auto additionalItems_opt = schema.find("additionalItems");

        if (!items_opt.has_value()) {
            return true;
        }
        const auto& items = items_opt.value();
        if (items.is_object()) {
            return std::all_of(value_arr.begin(), value_arr.end(), validate_with(items));
        }
        else if (items.is_array()) {
            const auto& items_arr = items.as_array();
            size_t maxi = std::max(items_arr.size(), value_arr.size());
            for (size_t i = 0; i < maxi; i++) {
                if (!validate(items_arr[i], value_arr[i])) {
                    return false;
                }
            }
            if (maxi < value_arr.size() && additionalItems_opt.has_value()) {
                return std::all_of(value_arr.begin() + maxi, value_arr.end(),
                                   validate_with(additionalItems_opt.value()));
            }
            return true;
        }
        else {
            throw schema_error();
        }
    }

    inline bool check_maxItems(const json::object& schema, const json::value& value)
    {
        if (!value.is_array()) {
            return true;
        }
        auto value_arr = value.as_array();

        auto maxItems_opt = schema.find("maxItems");
        if (!maxItems_opt.has_value()) {
            return true;
        }
        return value_arr.size() <= maxItems_opt.value().as_unsigned();
    }

    inline bool check_minItems(const json::object& schema, const json::value& value)
    {
        if (!value.is_array()) {
            return true;
        }
        auto value_arr = value.as_array();

        auto minItems_opt = schema.find("minItems");
        if (!minItems_opt.has_value()) {
            return true;
        }
        return value_arr.size() >= minItems_opt.value().as_unsigned();
    }

    inline bool check_uniqueItems(const json::object& schema, const json::value& value)
    {
        if (!value.is_array()) {
            return true;
        }
        auto value_arr = value.as_array();

        auto uniqueItems_opt = schema.find("uniqueItems");
        if (!uniqueItems_opt.has_value()) {
            return true;
        }
        const auto& uniqueItems = uniqueItems_opt.value();
        if (!uniqueItems.is_boolean()) {
            throw schema_error();
        }
        if (!uniqueItems.as_boolean()) {
            return true;
        }
        return is_unique(value_arr);
    }

    inline bool check_contains(const json::object& schema, const json::value& value)
    {
        if (!value.is_array()) {
            return true;
        }
        auto value_arr = value.as_array();

        auto contains_opt = schema.find("contains");
        if (!contains_opt.has_value()) {
            return true;
        }
        return std::any_of(value_arr.begin(), value_arr.end(), validate_with(contains_opt.value()));
    }

    inline bool check_maxProperties(const json::object& schema, const json::value& value)
    {
        if (!value.is_object()) {
            return true;
        }
        auto value_obj = value.as_object();

        auto maxProperties_opt = schema.find("maxProperties");
        if (!maxProperties_opt.has_value()) {
            return true;
        }
        return value_obj.size() <= maxProperties_opt.value().as_unsigned();
    }

    inline bool check_minProperties(const json::object& schema, const json::value& value)
    {
        if (!value.is_object()) {
            return true;
        }
        auto value_obj = value.as_object();

        auto minProperties_opt = schema.find("minProperties");
        if (!minProperties_opt.has_value()) {
            return true;
        }
        return value_obj.size() >= minProperties_opt.value().as_unsigned();
    }

    inline bool check_required(const json::object& schema, const json::value& value)
    {
        if (!value.is_object()) {
            return true;
        }
        auto value_obj = value.as_object();

        auto required_opt = schema.find("required");
        if (!required_opt.has_value()) {
            return true;
        }
        const auto& required = required_opt.value();
        if (!required.is_array()) {
            throw schema_error();
        }
        const auto& required_arr = required.as_array();
        if (std::all_of(required_arr.begin(), required_arr.end(), [](const auto& v) { return !v.is_string(); }) || !is_unique(required_arr)) {
            throw schema_error();
        }
        for (const auto& v: required_arr) {
            if (!value_obj.exists(v.as_string())) {
                return false;
            }
        }
        return true;
    }

    inline bool check_properties_patternProperties_additionalProperties(const json::object& schema, const json::value& value) {
        if (!value.is_object()) {
            return true;
        }
        const auto& value_obj = value.as_object();

        auto properties_opt = schema.find("properties");
        auto patternProperties_opt = schema.find("patternProperties");
        auto additionalProperties_opt = schema.find("additionalProperties");

        if (properties_opt.has_value() && !properties_opt.value().is_object()) {
            throw schema_error();
        }
        if (patternProperties_opt.has_value() && !patternProperties_opt.value().is_object()) {
            throw schema_error();
        }
        if (additionalProperties_opt.has_value() && !additionalProperties_opt.value().is_object()) {
            throw schema_error();
        }

        for (const auto& [key, subv] : value_obj) {
            bool evaluated = false;
            if (properties_opt.has_value()) {
                auto subs = properties_opt.value().as_object().find(key);
                if (subs.has_value()) {
                    evaluated = true;
                    if (!validate(subs.value(), subv)) {
                        return false;
                    }
                }
            }
            if (patternProperties_opt.has_value()) {
                for (const auto& [reg, subs] : patternProperties_opt.value().as_object()) {
                    std::regex regex(reg);
                    if (std::regex_match(key, regex)) {
                        evaluated = true;
                        if (!validate(subs, subv)) {
                            return false;
                        }
                    }
                }
            }
            if (!evaluated && additionalProperties_opt.has_value()) {
                if (!validate(additionalProperties_opt.value(), subv)) {
                    return false;
                }
            }
        }

        return true;
    }

    inline bool check_dependencies(const json::object& schema, const json::value& value) {
        if (!value.is_object()) {
            return true;
        }
        const auto& value_obj = value.as_object();

        auto dependencies_opt = schema.find("dependencies");
        if (!dependencies_opt.has_value()) {
            return true;
        }
        const auto& dependencies = dependencies_opt.value();
        if (!dependencies.is_object()) {
            throw schema_error();
        }

        for (const auto& [prop, subs] : dependencies.as_object()) {
            if (value_obj.exists(prop)) {
                if (subs.is_array()) {
                    const auto& subs_arr = subs.as_array();
                    if (std::any_of(subs_arr.begin(), subs_arr.end(), [](const auto& v) { return !v.is_string(); }) || !is_unique(subs_arr)) {
                        throw schema_error();
                    }
                    if (std::any_of(subs_arr.begin(), subs_arr.end(), [&value_obj](const auto& v) {
                        return !value_obj.exists(v.as_string());
                    })) {
                        return false;
                    }
                } else if (subs.is_object()) {
                    if (!validate(subs, value_obj)) {
                        return false;
                    }
                } else {
                    throw schema_error();
                }
            }
        }
        return true;
    }

    inline bool check_propertyNames(const json::object& schema, const json::value& value)
    {
        if (!value.is_object()) {
            return true;
        }
        auto value_obj = value.as_object();

        auto propertyNames_opt = schema.find("propertyNames");
        if (!propertyNames_opt.has_value()) {
            return true;
        }
        const auto& propertyNames = propertyNames_opt.value();
        return std::all_of(value_obj.begin(), value_obj.end(), [&propertyNames](const auto& pr) {
            return validate(propertyNames, pr.first);
        });
    }

    inline bool check_if_then_else(const json::object& schema, const json::value& value)
    {
        auto if_opt = schema.find("if");
        if (!if_opt.has_value()) {
            return true;
        }
        const auto& if_ = if_opt.value();
        if (validate(if_, value)) {
            auto then_opt = schema.find("then");
            if (!then_opt.has_value()) {
                return true;
            }
            return validate(then_opt.value(), value);
        }
        else {
            auto else_opt = schema.find("else");
            if (!else_opt.has_value()) {
                return true;
            }
            return validate(else_opt.value(), value);
        }
    }

    inline bool check_allOf(const json::object& schema, const json::value& value)
    {
        auto allOf_opt = schema.find("allOf");
        if (!allOf_opt.has_value()) {
            return true;
        }
        const auto& allOf = allOf_opt.value();
        if (!allOf.is_array()) {
            throw schema_error();
        }
        const auto& allOf_arr = allOf.as_array();
        if (allOf_arr.size() == 0) {
            throw schema_error();
        }
        return std::all_of(allOf_arr.begin(), allOf_arr.end(),
                           [&value](const json::value& subs) { return validate(subs, value); });
    }

    inline bool check_anyOf(const json::object& schema, const json::value& value)
    {
        auto anyOf_opt = schema.find("anyOf");
        if (!anyOf_opt.has_value()) {
            return true;
        }
        const auto& anyOf = anyOf_opt.value();
        if (!anyOf.is_array()) {
            throw schema_error();
        }
        const auto& anyOf_arr = anyOf.as_array();
        if (anyOf_arr.size() == 0) {
            throw schema_error();
        }
        return std::any_of(anyOf_arr.begin(), anyOf_arr.end(),
                           [&value](const json::value& subs) { return validate(subs, value); });
    }

    inline bool check_oneOf(const json::object& schema, const json::value& value)
    {
        auto oneOf_opt = schema.find("oneOf");
        if (!oneOf_opt.has_value()) {
            return true;
        }
        const auto& oneOf = oneOf_opt.value();
        if (!oneOf.is_array()) {
            throw schema_error();
        }
        const auto& oneOf_arr = oneOf.as_array();
        if (oneOf_arr.size() == 0) {
            throw schema_error();
        }
        size_t counter = 0;
        for (const auto& subs : oneOf_arr) {
            if (validate(subs, value)) {
                counter++;
            }
            if (counter > 1) {
                return false;
            }
        }
        return counter == 1;
    }

    inline bool check_not(const json::object& schema, const json::value& value)
    {
        auto not_opt = schema.find("not");
        if (!not_opt.has_value()) {
            return true;
        }
        return !validate(not_opt.value(), value);
    }

    inline bool validate(const json::value& schemav, const json::value& value)
    {
        if (!schemav.is_object()) {
            throw schema_error();
        }
        using checker = bool (*)(const json::object& schema, const json::value& value);
        constexpr const checker checkers[] = { check_type,
                                               check_enum,
                                               check_const,
                                               check_multipleOf,
                                               check_maximum,
                                               check_exclusiveMaximum,
                                               check_minimum,
                                               check_exclusiveMinimum,
                                               check_maxLength,
                                               check_minLength,
                                               check_pattern,
                                               check_items_additionalItems,
                                               check_maxItems,
                                               check_minItems,
                                               check_uniqueItems,
                                               check_contains,
                                               check_maxProperties,
                                               check_minProperties,
                                               check_required,
                                               check_properties_patternProperties_additionalProperties,
                                               check_dependencies,
                                               check_propertyNames,
                                               check_if_then_else,
                                               check_allOf,
                                               check_anyOf,
                                               check_oneOf,
                                               check_not };
        const auto& schema = schemav.as_object();
        for (auto ch : checkers) {
            if (!ch(schema, value)) {
                return false;
            }
        }
        return true;
    }

} // namespace json_schema

} // namespace lhg
