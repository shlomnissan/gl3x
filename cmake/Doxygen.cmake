# Doxygen.cmake
#
# This CMake module automates the generation of API documentation using Doxygen.
# It checks if Doxygen is installed and, if available, sets up a custom build target
# to generate the documentation.
#
# Usage:
# Run the following command to generate the documentation:
#   cmake --build . --target doxygen
#
# If Doxygen is not installed, a warning will be displayed.

find_package(Doxygen)

if (DOXYGEN_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        doxygen-awesome-css
        URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    FetchContent_MakeAvailable(doxygen-awesome-css)
    FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else()
    message(WARNING "Please ensure that Doxygen is installed on your system.")
endif()