/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>

#include <gleam/core/geometry.hpp>

#include <vector>

using enum gleam::GeometryAttributeType;

#pragma region Constructors

TEST(Geometry, DefaultConstruction) {
    const auto geometry = gleam::Geometry::Create();

    EXPECT_TRUE(geometry->VertexData().empty());
    EXPECT_TRUE(geometry->IndexData().empty());
    EXPECT_TRUE(geometry->Attributes().empty());
}

TEST(Geometry, InitializeWithVertexAndIndexData) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    const auto index_data = std::vector<unsigned int>{0, 1, 2};
    const auto geometry = gleam::Geometry::Create(vertex_data, index_data);

    EXPECT_EQ(geometry->VertexData().size(), 3);
    EXPECT_EQ(geometry->IndexData().size(), 3);
}

TEST(Geometry, InitializeWithVertexData) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    const auto geometry = gleam::Geometry::Create(vertex_data);

    EXPECT_EQ(geometry->VertexData().size(), 3);
    EXPECT_TRUE(geometry->IndexData().empty());
}

#pragma endregion

#pragma region Attributes

TEST(Geometry, AddAttribute) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    auto geometry = gleam::Geometry::Create(vertex_data);

    geometry->SetAttribute({.type = Position, .item_size = 3});

    const auto& attribs = geometry->Attributes();

    EXPECT_EQ(attribs.size(), 1);
    EXPECT_EQ(attribs.front().type, Position);
    EXPECT_EQ(attribs.front().item_size, 3);
}

TEST(Geometry, AddMultipleAttributes) {
    const auto vertex_data = std::vector<float>{
        0.0f, 1.0f, 2.0f, 0.33f, 0.55f
    };

    auto geometry = gleam::Geometry::Create(vertex_data);
    geometry->SetAttribute({.type = Position, .item_size = 3});
    geometry->SetAttribute({.type = UV, .item_size = 2});

    const auto& attribs = geometry->Attributes();

    EXPECT_EQ(attribs.size(), 2);
    EXPECT_EQ(attribs.front().type, Position);
    EXPECT_EQ(attribs.back().type, UV);
}

TEST(Geometry, ReturnsTrueIfAttributeExists) {
    auto geometry = gleam::Geometry::Create({
        0.0f, 1.0f, 2.0f
    });

    geometry->SetAttribute({.type = Position, .item_size = 3});

    EXPECT_TRUE(geometry->HasAttribute(Position));
}

TEST(Geometry, ReturnsFalseIfAttributeDoesNotExist) {
    auto geometry = gleam::Geometry::Create({
        0.0f, 1.0f, 2.0f
    });

    geometry->SetAttribute({.type = Position, .item_size = 3});

    EXPECT_FALSE(geometry->HasAttribute(UV));
}

#pragma endregion

#pragma region Vertex Count

TEST(Geometry, Stride) {
    const auto vertex_data = std::vector<float>{
        0.0f, 1.0f, 2.0f, 0.33f, 0.55f,
        0.0f, 1.0f, 2.0f, 0.33f, 0.55f
    };

    auto geometry = gleam::Geometry::Create(vertex_data);
    geometry->SetAttribute({.type = Position, .item_size = 3});
    geometry->SetAttribute({.type = UV, .item_size = 2});

    EXPECT_EQ(geometry->Stride(), 5);
}

TEST(Geometry, VertexCount) {
    auto vertex_data = std::vector<float> {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    auto geometry = gleam::Geometry::Create(vertex_data);
    geometry->SetAttribute({.type = Position, .item_size = 3});

    EXPECT_EQ(geometry->VertexCount(), 3);
}

#pragma endregion

#pragma region Edge Cases

TEST(Geometry, AddAttributeWithZeroItemSize) {
    const auto vertex_data = std::vector<float>{0.0f, 1.0f, 2.0f};
    auto geometry = gleam::Geometry::Create(vertex_data);

    EXPECT_DEATH({
        geometry->SetAttribute({.type = Position, .item_size = 0});
    }, ".*attribute.item_size > 0");
}

#pragma endregion