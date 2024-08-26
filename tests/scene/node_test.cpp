// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/scene/node.hpp>

#pragma region Node Operations

TEST(Node, AddChild) {
    auto parent = engine::Node::Create();
    auto child = engine::Node::Create();

    parent->Add(child);

    EXPECT_EQ(parent->Children().size(), 1);
    EXPECT_EQ(parent->Children()[0], child);
}

TEST(Node, RemoveChild) {
    auto parent = engine::Node::Create();
    auto child = engine::Node::Create();

    parent->Add(child);
    parent->Remove(child);

    EXPECT_TRUE(parent->Children().empty());
}

#pragma endregion

#pragma region Transformations

TEST(Node, ScaleTransform) {

}

TEST(Node, RotateXTransform) {

}

TEST(Node, TranslateXTransform) {

}

#pragma endregion

#pragma region Update Transforms

TEST(Node, UpdateTransformsWithoutParent) {

}

TEST(Node, UpdateTransformsWithParent) {

}

#pragma endregion

#pragma region ShouldUpdate Checks

TEST(Node, ShouldUpdateTransformWhenDirty) {

}

TEST(Node, ShouldUpdateTransformWhenParentDirty) {

}

#pragma endregion

#pragma region Edge Cases

TEST(Node, AddChildWithExistingParent) {

}

TEST(Node, RemoveNonexistentChild) {

}

#pragma endregion