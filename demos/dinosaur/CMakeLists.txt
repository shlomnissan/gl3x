# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

add_executable(dinosaur-runner src/main.cpp)

target_link_libraries(dinosaur-runner PRIVATE engine)