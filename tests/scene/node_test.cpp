// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/scene/node.hpp>

// TODO: add tests

TEST(NodeTest, AddChild) {
    const auto parent = engine::Node::Create();
    const auto child = engine::Node::Create();

    parent->Add(child);

    EXPECT_EQ(parent->Children().size(), 1);
    EXPECT_EQ(parent->Children().front(), child);
    EXPECT_EQ(child->Parent(), parent.get());
}