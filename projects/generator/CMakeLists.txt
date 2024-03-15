find_program(NODE_EXE NAMES node nodejs)

if(NOT NODE_EXE)
    message(FATAL_ERROR "NodeJS not found")
endif()

set(LHG_GENERATOR_JS
    ${CMAKE_CURRENT_LIST_DIR}/dist/new.js
    CACHE STRING "[LHG] Path to generator")

function(LHGGenerate target interface_path config_path output_path)
    add_custom_command(
        OUTPUT ${output_path}
        COMMAND ${NODE_EXE} ${LHG_GENERATOR_JS} ${interface_path} ${config_path} ${output_path}
        DEPENDS ${LHG_GENERATOR_JS} ${interface_path} ${config_path}
        COMMENT "LHG: Generate ${output_path}"
        VERBATIM)
    add_custom_target(${target} DEPENDS ${output_path})
endfunction()
