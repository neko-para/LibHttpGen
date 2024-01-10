#pragma once

#include <meojson/json.hpp>

namespace lhg
{

namespace json_schema
{

    using schema = json::cobject;

    struct schema_validation_failed : std::exception
    {
        std::string error;
        schema_validation_failed(const char* err) : error(err) {}

        virtual const char* what() const noexcept { return error.c_str(); }
    };

    constexpr bool __check_type(std::string type)
    {
        return type == "null" || type == "boolean" || type == "object" || type == "array" || type == "number" ||
               type == "string" || type == "integer";
    }

    template <typename container_t>
    constexpr bool __check_unique(container_t data)
    {
        for (auto test = data.begin(); test != data.end(); test++) {
            for (auto target = data.begin(); target != test; target++) {
                if (*test == *target) {
                    return false;
                }
            }
        }
        return true;
    }

    constexpr schema make_type(std::string type)
    {
        if (!__check_type(type)) {
            throw schema_validation_failed { "type invalid" };
        }
        return { { "type", type } };
    }

    constexpr schema make_type(std::initializer_list<std::string> types)
    {
        if (!__check_unique(types)) {
            throw schema_validation_failed { "type is not unique" };
        }
        for (auto type : types) {
            if (!__check_type(type)) {
                throw schema_validation_failed { "type invalid" };
            }
        }
        return { { "type", json::carray(types) } };
    }

    constexpr schema make_enum

}

}
