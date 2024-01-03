file(GLOB_RECURSE srcs sources/*.h sources/*.hpp sources/*.cpp)
add_executable(LHGInterfaceExtractor ${srcs})
target_include_directories(LHGInterfaceExtractor PRIVATE sources)
target_link_libraries(LHGInterfaceExtractor LHGHeaderonly Boost::system LHGClangCpp)
