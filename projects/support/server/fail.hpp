#pragma once

#include <iostream>

#include "utils/forward.hpp"

namespace lhg::server
{

inline void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << std::endl;
}

}
