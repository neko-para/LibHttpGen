#pragma once

#include <string>

#include "constexpr_map.hpp"
#include "constexpr_unique_ptr.hpp"
#include "constexpr_variant.hpp"

namespace json
{

template <typename elem_t>
constexpr bool soft_is_digit(elem_t ch)
{
    return '0' <= ch && ch <= '9';
}

template <typename string_t>
constexpr string_t soft_to_string(unsigned long long value)
{
    string_t result;
    do {
        result.push_back('0' + value % 10);
        value /= 10;
    } while (value > 0);
    return string_t(result.rbegin(), result.rend());
}

template <typename string_t>
constexpr string_t soft_to_string(long long value)
{
    string_t result;
    bool nega = false;
    if (value == INT64_MIN) {
        return soft_to_string<string_t>(0x8000000000000000ull);
    }
    if (value < 0) {
        nega = true;
        value = -value;
    }
    do {
        result.push_back('0' + value % 10);
        value /= 10;
    } while (value > 0);
    if (nega) {
        result.push_back('-');
    }
    return string_t(result.rbegin(), result.rend());
}

template <typename string_t>
constexpr string_t soft_to_string(double value)
{
    string_t result;
    if (value < 0) {
        result.push_back('-');
        value = -value;
    }
    int precision = 14;
    double base = 1;
    while (base < value) {
        base *= 10;
    }
    while (precision--) {
        base /= 10;
        char c = '0';
        while (value >= base) {
            value -= base;
            c++;
        }
        result.push_back(c);
        if (base == 1) {
            result.push_back('.');
        }
    }
    return result;
}

template <typename string_t>
constexpr string_t soft_to_string(signed char v)
{
    return soft_to_string<string_t>(static_cast<long long>(v));
}
template <typename string_t>
constexpr string_t soft_to_string(short v)
{
    return soft_to_string<string_t>(static_cast<long long>(v));
}
template <typename string_t>
constexpr string_t soft_to_string(int v)
{
    return soft_to_string<string_t>(static_cast<long long>(v));
}
template <typename string_t>
constexpr string_t soft_to_string(long v)
{
    return soft_to_string<string_t>(static_cast<long long>(v));
}

template <typename string_t>
constexpr string_t soft_to_string(unsigned char v)
{
    return soft_to_string<string_t>(static_cast<unsigned long long>(v));
}
template <typename string_t>
constexpr string_t soft_to_string(unsigned short v)
{
    return soft_to_string<string_t>(static_cast<unsigned long long>(v));
}
template <typename string_t>
constexpr string_t soft_to_string(unsigned int v)
{
    return soft_to_string<string_t>(static_cast<unsigned long long>(v));
}
template <typename string_t>
constexpr string_t soft_to_string(unsigned long v)
{
    return soft_to_string<string_t>(static_cast<unsigned long long>(v));
}

template <typename string_t>
constexpr string_t soft_to_string(float v)
{
    return soft_to_string<string_t>(static_cast<double>(v));
}
template <typename string_t>
constexpr string_t soft_to_string(long double v)
{
    return soft_to_string<string_t>(static_cast<double>(v));
}

}; // namespace json
