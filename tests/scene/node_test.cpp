// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include "scene/node.hpp"

#include <memory>

// TODO: add tests

TEST(NodeTest, AddChild) {
    const auto parent = std::make_shared<engine::Node>();
    const auto child = std::make_shared<engine::Node>();

    parent->Add(child);

    EXPECT_EQ(parent->Children().size(), 1);
    EXPECT_EQ(parent->Children().front(), child);
    EXPECT_EQ(child->Parent(), parent.get());
}