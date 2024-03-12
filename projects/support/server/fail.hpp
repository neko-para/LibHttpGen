#pragma once

#include <iostream>

#include "utils/boost.hpp"

namespace lhg::server
{

inline void fail(beast::error_code ec, const char* what)
{
    std::cerr << what << ": " << ec.message() << std::endl;
}

}
