file(GLOB_RECURSE srcs *.h *.hpp *.cpp)
add_executable(LHGTarget ${srcs})
target_include_directories(LHGTarget PRIVATE . ../maa/include)
target_link_libraries(LHGTarget Headeronly Boost::system
                      MaaFramework::MaaFramework)
