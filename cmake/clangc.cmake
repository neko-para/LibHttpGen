find_package(LLVM CONFIG REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

include(HandleLLVMOptions)

add_library(ClangC SHARED IMPORTED)

target_compile_definitions(ClangC INTERFACE ${LLVM_DEFINITIONS})

if(WIN32)
  find_file(
    CLANG_C_DLL_DEBUG
    NAMES libclang.dll
    PATHS ${LLVM_INCLUDE_DIR}/../debug/bin REQUIRED)
  find_file(
    CLANG_C_DLL_RELEASE
    NAMES libclang.dll
    PATHS ${LLVM_INCLUDE_DIR}/../bin REQUIRED)
  message("clangc found debug: ${CLANG_C_DLL_DEBUG}")
  message("clangc found release: ${CLANG_C_DLL_RELEASE}")
  find_library(CLANG_C_LIB_DEBUG libclang NO_DEFAULT_PATH
               PATHS ${LLVM_INCLUDE_DIR}/../debug/lib REQUIRED)
  find_library(CLANG_C_LIB_RELEASE libclang NO_DEFAULT_PATH
               PATHS ${LLVM_INCLUDE_DIR}/../lib REQUIRED)
  message("clangc found debug imp: ${CLANG_C_LIB_DEBUG}")
  message("clangc found release imp: ${CLANG_C_LIB_RELEASE}")

  set_property(
    TARGET ClangC
    APPEND
    PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
  set_target_properties(
    ClangC
    PROPERTIES IMPORTED_LOCATION_DEBUG "${CLANG_C_DLL_DEBUG}"
               IMPORTED_IMPLIB_DEBUG "${CLANG_C_LIB_DEBUG}"
               INTERFACE_INCLUDE_DIRECTORIES "${LLVM_INCLUDE_DIR}")

  set_property(
    TARGET ClangC
    APPEND
    PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
  set_target_properties(
    ClangC
    PROPERTIES IMPORTED_LOCATION_RELEASE "${CLANG_C_DLL_RELEASE}"
               IMPORTED_IMPLIB_RELEASE "${CLANG_C_LIB_RELEASE}"
               INTERFACE_INCLUDE_DIRECTORIES "${LLVM_INCLUDE_DIR}")
else()
  find_library(CLANG_C_LIB_DEBUG clang NO_DEFAULT_PATH
               PATHS "${LLVM_INCLUDE_DIR}/../debug/lib" REQUIRED)
  find_library(CLANG_C_LIB_RELEASE clang NO_DEFAULT_PATH
               PATHS "${LLVM_INCLUDE_DIR}/../lib" REQUIRED)
  message("clangc found debug: ${CLANG_C_LIB_DEBUG}")
  message("clangc found release: ${CLANG_C_LIB_RELEASE}")

  set_property(
    TARGET ClangC
    APPEND
    PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
  set_target_properties(
    ClangC PROPERTIES IMPORTED_LOCATION_DEBUG "${CLANG_C_LIB_DEBUG}"
                      INTERFACE_INCLUDE_DIRECTORIES "${LLVM_INCLUDE_DIR}")

  set_property(
    TARGET ClangC
    APPEND
    PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
  set_target_properties(
    ClangC PROPERTIES IMPORTED_LOCATION_RELEASE "${CLANG_C_LIB_RELEASE}"
                      INTERFACE_INCLUDE_DIRECTORIES "${LLVM_INCLUDE_DIR}")

endif()
