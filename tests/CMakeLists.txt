if (BUILD_SHARED_LIBS)
    message(FATAL_ERROR "
        ⚠️ Unit tests should be built in conjunction with a static library.\n
        -- -DBUILD_SHARED_LIBS=0 or -DBUILD_TESTS=0
    ")
endif()

set(BUILD_GMOCK OFF CACHE BOOL "")

find_package(GTest REQUIRED)

if (NOT GTest_FOUND)
    message(FATAL_ERROR "
        ⚠️ GTest was not found. Use conan to install missing depedencies.
        -- conan install . --output-folder=build --build=missing
    ")
endif()

file(GLOB TEST_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/**/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/**/**/*.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_LIST_DIR})

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/assets.stamp
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/assets.stamp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

add_custom_target(copy_assets ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/assets.stamp
)

foreach(TEST IN LISTS TEST_SOURCES)
    get_filename_component(FILE_NAME ${TEST} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" NAME_NO_EXT ${FILE_NAME})
    message(STATUS "🧪 Adding test ${FILE_NAME}")

    set(TEST_TARGET run_${NAME_NO_EXT})
    add_executable(${TEST_TARGET} test_helpers.hpp ${TEST})
    target_link_libraries(${TEST_TARGET} PRIVATE GTest::gtest GTest::gtest_main engine)
    add_test(${NAME_NO_EXT} ${TEST_TARGET})

    add_dependencies(${TEST_TARGET} copy_assets)
endforeach()