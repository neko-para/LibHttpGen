#pragma once

#ifdef USE_FMTLIB

#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace FMT
{
using fmt::format;
}

#else

#include <format>

namespace FMT
{
using std::format;
}

#endif
