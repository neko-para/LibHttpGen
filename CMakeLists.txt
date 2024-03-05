cmake_minimum_required(VERSION 3.24)
project(LibHttpGen)

if(NOT LHG_EMBEDDED)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

  if(APPLE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    set(CMAKE_INSTALL_RPATH "@executable_path")
  elseif(UNIX)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
  endif()

  if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    add_compile_options("/EHsc")
  endif()
endif()

find_package(Boost REQUIRED COMPONENTS system)
add_subdirectory(3rdparty)

if(NOT LHG_EMBEDDED)
  include(cmake/clangc.cmake)
endif()

if(NOT LHG_EMBEDDED)
  add_subdirectory(projects/clang-cpp)
  add_subdirectory(projects/interface-extractor)
endif()

add_subdirectory(projects/support)
