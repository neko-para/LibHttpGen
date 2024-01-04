#pragma once

#include <meojson/json.hpp>

namespace lhg
{

template <typename Type>
Type output_prepare() = delete;

template <typename Type>
json::value output_finalize(Type v) = delete;

}
