# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

add_executable(example main.cpp)

# Why is glad needed?
find_package(glad REQUIRED)

target_link_libraries(example PRIVATE engine glad::glad)