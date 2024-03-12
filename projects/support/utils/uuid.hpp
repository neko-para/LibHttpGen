#pragma once

#include "utils/boost.hpp"

namespace lhg
{

inline std::string make_uuid()
{
    static auto uuid_generator = boost::uuids::random_generator();

    return boost::uuids::to_string(uuid_generator());
}

}
