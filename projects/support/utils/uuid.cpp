#include "utils/uuid.hpp"
#include "utils/forward.hpp"

namespace lhg {

auto uuid_generator = boost::uuids::random_generator();
std::string make_uuid()
{
    return boost::uuids::to_string(uuid_generator());
}

}
