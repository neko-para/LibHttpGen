file(GLOB_RECURSE srcs sources/*.h sources/*.hpp sources/*.cpp)
add_library(LHGRegenerator SHARED ${srcs})
target_include_directories(
  LHGRegenerator
  PRIVATE sources
  PUBLIC include)
target_link_libraries(LHGRegenerator Headeronly Boost::system)
