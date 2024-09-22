# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

add_executable(engine-examples main.cpp)

target_link_libraries(engine-examples PRIVATE engine)

add_custom_command(
    TARGET engine-examples POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:engine-examples>/assets
)