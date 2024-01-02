file(GLOB_RECURSE srcs *.h *.hpp *.cpp)
add_executable(LHGTarget ${srcs})
target_include_directories(LHGTarget PRIVATE . ../maa/include)
target_link_libraries(LHGTarget Headeronly Boost::system
                      MaaFramework::MaaFramework MaaFramework::MaaToolKit)

install(
  TARGETS LHGTarget
          RUNTIME_DEPENDENCIES
          PRE_EXCLUDE_REGEXES
          "api-ms-"
          "ext-ms-"
          POST_EXCLUDE_REGEXES
          ".*system32/.*\\.dll"
          DIRECTORIES
          maa/bin
  RUNTIME DESTINATION .
  LIBRARY DESTINATION .
  FRAMEWORK DESTINATION .)
