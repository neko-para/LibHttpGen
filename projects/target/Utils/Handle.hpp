#pragma once

#include <meojson/json.hpp>

#include "Helper/HandleManager.hpp"

namespace lhg {

template <typename F>
using opaque_manager = HandleManager<F>;

}
