add_library(LHGHeaderonly INTERFACE)
target_include_directories(LHGHeaderonly INTERFACE include)
if(APPLE)
  target_compile_definitions(LHGHeaderonly INTERFACE LHG_USE_FMTLIB)
endif()
