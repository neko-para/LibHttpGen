#pragma once

#ifdef USE_FMTLIB

#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace LHGFMT = fmt;

#else

#include <format>

namespace LHGFMT = std;

#endif
