file(GLOB_RECURSE lhg_support_src *.cpp *.hpp *.h)

add_library(LhgSupport SHARED ${lhg_support_src})
target_include_directories(LhgSupport PRIVATE .)
target_link_libraries(LhgSupport LHGHeaderonly Boost::system)

if(WIN32)
  target_compile_definitions(LhgSupport PRIVATE _WIN32_WINNT=0x0A00)
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${lhg_support_src})
