// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/core/geometry.hpp>

#include <vector>

using enum engine::GeometryAttributeType;

#pragma region Constructors

TEST(Geometry, DefaultConstruction) {
    const auto geometry = engine::Geometry::Create();

    EXPECT_TRUE(geometry->VertexData().empty());
    EXPECT_TRUE(geometry->IndexData().empty());
    EXPECT_TRUE(geometry->Attributes().empty());
}

TEST(Geometry, InitializeWithVertexAndIndexData) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    const auto index_data = std::vector<unsigned int>{0, 1, 2};
    const auto geometry = engine::Geometry::Create(vertex_data, index_data);

    EXPECT_EQ(geometry->VertexData().size(), 3);
    EXPECT_EQ(geometry->IndexData().size(), 3);
}

TEST(Geometry, InitializeWithVertexData) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    const auto geometry = engine::Geometry::Create(vertex_data);

    EXPECT_EQ(geometry->VertexData().size(), 3);
    EXPECT_TRUE(geometry->IndexData().empty());
}

#pragma endregion

#pragma region Attributes

TEST(Geometry, AddAttribute) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    auto geometry = engine::Geometry::Create(vertex_data);

    geometry->SetAttribute({.type = kPosition, .item_size = 3, .offset = 0});

    const auto& attribs = geometry->Attributes();

    EXPECT_EQ(attribs.size(), 1);
    EXPECT_EQ(attribs.front().type, kPosition);
    EXPECT_EQ(attribs.front().item_size, 3);
    EXPECT_EQ(attribs.front().offset, 0);
}

TEST(Geometry, AddMultipleAttributes) {
    const auto vertex_data = std::vector<float>{
        0.0f, 1.0f, 2.0f, 0.33f, 0.55f
    };

    auto geometry = engine::Geometry::Create(vertex_data);
    geometry->SetAttribute({.type = kPosition, .item_size = 3, .offset = 0});
    geometry->SetAttribute({.type = kUV, .item_size = 2, .offset = 3});

    const auto& attribs = geometry->Attributes();

    EXPECT_EQ(attribs.size(), 2);
    EXPECT_EQ(attribs.front().type, kPosition);
    EXPECT_EQ(attribs.back().type, kUV);
}

#pragma endregion

#pragma region Edge Cases

TEST(Geometry, AddAttributeWithZeroItemSize) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    auto geometry = engine::Geometry::Create(vertex_data);

    EXPECT_DEATH({
        geometry->SetAttribute({.type = kPosition, .item_size = 0, .offset = 0});
    }, ".*attribute.item_size > 0");
}

TEST(Geometry, AddAttributeWithInvalidOffset) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    auto geometry = engine::Geometry::Create(vertex_data);

    EXPECT_DEATH({
        geometry->SetAttribute({.type = kPosition, .item_size = 3, .offset = 100});
    }, ".*attribute.offset < vertex_data_.size");
}

#pragma endregion