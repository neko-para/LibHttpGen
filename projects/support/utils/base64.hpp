#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace lhg
{

namespace pri
{

constexpr std::string_view base64_charset =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

}

inline std::string to_base64(std::string_view data)
{
    std::string result;
    int phase = 0;
    int pending = 0;

    for (auto ch : data) {
        switch (phase) {
        case 0:
            result.push_back(pri::base64_charset[ch >> 2]);
            pending = (ch & 3) << 4;
            phase = 1;
            break;
        case 1:
            result.push_back(pri::base64_charset[pending | (ch >> 4)]);
            pending = (ch & 15) << 2;
            phase = 2;
            break;
        case 2:
            result.push_back(pri::base64_charset[pending | (ch >> 6)]);
            result.push_back(pri::base64_charset[ch & 63]);
            pending = 0;
            phase = 0;
            break;
        }
    }
    if (phase == 1) {
        result.push_back(pri::base64_charset[pending]);
        result.append("==");
    }
    else if (phase == 2) {
        result.push_back(pri::base64_charset[pending]);
        result.append("=");
    }

    return result;
}

inline std::optional<std::string> from_base64(std::string_view data)
{
    if (data.length() % 4) {
        return std::nullopt;
    }

    std::string result;
    int pending = 0, pending_bit = 0;

    for (auto ch : data) {
        if (ch == '=') {
            if (pending_bit >= 2) {
                pending_bit -= 2;
            }
            else {
                return std::nullopt;
            }
        }
        else {
            auto val = pri::base64_charset.find(ch);
            pending <<= 6;
            pending |= val;
            pending_bit += 6;
            if (pending_bit >= 8) {
                int rest_bit = pending_bit - 8;
                result.push_back(static_cast<char>((pending >> rest_bit) & 0xFF));
                pending &= (1 << rest_bit) - 1;
                pending_bit -= 8;
            }
        }
    }
    if (pending_bit > 0) {
        return std::nullopt;
    }
    else {
        return result;
    }
}

}
