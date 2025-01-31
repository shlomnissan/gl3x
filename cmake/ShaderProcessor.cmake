# ShaderProcessor.cmake
#
# This module searches for GLSL files and converts them into C-style strings.
# It also manages dynamic inclusion through the "#include <chunk>" directive.

file(GLOB_RECURSE SHADERS "**/*.vert" "**/*.frag")

function(ResolveIncludes CONTENTS OUTPUT_STR)
    set(OUTPUT "${CONTENTS}")
    while (OUTPUT MATCHES "#include[ ]*\"([^\"]+)\"")
        set(INCLUDE_FILE "${DIRECTORY}/${CMAKE_MATCH_1}")
        if (EXISTS ${INCLUDE_FILE})
            file(READ ${INCLUDE_FILE} INCLUDED_CONTENTS)
            set(START "\n// Start of included file ${CMAKE_MATCH_1}\n")
            set(END "\n// End of included file ${CMAKE_MATCH_1}\n")
            string(REPLACE "#include \"${CMAKE_MATCH_1}\"" "${START}${INCLUDED_CONTENTS}${END}" OUTPUT "${OUTPUT}")
        else()
            message(FATAL_ERROR "Shader snippet not found: ${INCLUDE_FILE}")
        endif()
    endwhile()
    set(${OUTPUT_STR} "${OUTPUT}" PARENT_SCOPE)
endfunction()

foreach(SHADER IN LISTS SHADERS)
    get_filename_component(FILENAME ${SHADER} NAME)
    get_filename_component(DIRECTORY ${SHADER} DIRECTORY)
    get_filename_component(EXTENSION ${SHADER} EXT)

    string(REGEX REPLACE "\\." "_" EXT ${EXTENSION})
    string(REGEX REPLACE "\\.[^.]*$" "" FILENAME_NO_EXT ${FILENAME})
    set(HEADER_FILE ${DIRECTORY}/headers/${FILENAME_NO_EXT}${EXT}.h)

    message("🎨 Writing shader ${FILENAME_NO_EXT}.h")

    file(READ ${SHADER} SHADER_CONTENTS)
    ResolveIncludes("${SHADER_CONTENTS}" PROCESSED_SHADER)

    file(WRITE ${HEADER_FILE} "#pragma once\n\nstatic const char* _SHADER_${FILENAME_NO_EXT}${EXT} = R\"(")
    file(APPEND ${HEADER_FILE} "${PROCESSED_SHADER}")
    file(APPEND ${HEADER_FILE} ")\";")
endforeach()