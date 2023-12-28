file(GLOB_RECURSE srcs sources/*.h sources/*.hpp sources/*.cpp)
add_executable(LHGInterfaceBuilder ${srcs})
target_include_directories(LHGInterfaceBuilder PRIVATE sources)
target_link_libraries(LHGInterfaceBuilder Headeronly Boost::system
                      LHGRegenerator)
