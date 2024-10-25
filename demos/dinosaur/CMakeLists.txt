# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

set(SOURCE_CODE
    "dinosaur.cpp"
    "dinosaur.hpp"
    "game.cpp"
    "game.hpp"
    "ground.cpp"
    "ground.hpp"
    "main.cpp"
)

add_executable(dinosaur-runner ${SOURCE_CODE})

target_link_libraries(dinosaur-runner PRIVATE engine)