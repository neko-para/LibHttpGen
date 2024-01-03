#pragma once

#include "Helper/Forward.hpp"

#include <iostream>

inline void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << std::endl;
}
