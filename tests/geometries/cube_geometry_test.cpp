/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>

#include <gleam/geometries/cube_geometry.hpp>

#pragma region Fixtures

class CubeGeometryTest : public ::testing::Test {
protected:
    gleam::CubeGeometry cube_ {{
        .width = 1.0f,
        .height = 1.0f,
        .depth = 1.0f,
        .width_segments = 2,
        .height_segments = 2,
        .depth_segments = 2
    }};
};

#pragma endregion

#pragma region Constructor

TEST_F(CubeGeometryTest, ConstructorInitializesVertexData) {
    const auto& verts = cube_.VertexData();

    // 8 values per vertex, 9 vertices, 6 faces
    EXPECT_EQ(verts.size(), 8 * 9 * 6);
}

TEST_F(CubeGeometryTest, ConstructorInitializesIndexData) {
    const auto& index = cube_.IndexData();

    // 6 indices (2 triangles per sub-plane), 4 sub-planes, 6 faces
    EXPECT_EQ(index.size(), 6 * 4 * 6);
}

TEST_F(CubeGeometryTest, ConstructorInitializesName) {
    EXPECT_EQ(cube_.Name(), "cube geometry");
}

#pragma endregion

#pragma region Attributes

TEST_F(CubeGeometryTest, AttributesConfiguredCorrectly) {
    using enum gleam::VertexAttributeType;

    const auto& attrs = cube_.Attributes();

    EXPECT_EQ(attrs.size(), 3);
    EXPECT_EQ(attrs[0].type, Position);
    EXPECT_EQ(attrs[0].item_size, 3u);
    EXPECT_EQ(attrs[1].type, Normal);
    EXPECT_EQ(attrs[1].item_size, 3u);
    EXPECT_EQ(attrs[2].type, UV);
    EXPECT_EQ(attrs[2].item_size, 2u);
}

#pragma endregion

#pragma region Assertions

TEST(CubeGeometry, DeathWhenParamsAreInvalid) {
    EXPECT_DEATH({
        gleam::CubeGeometry({.width = 0.0f});
    }, ".*params.width > 0");

    EXPECT_DEATH({
        gleam::CubeGeometry({.height = 0.0f});
    }, ".*params.height > 0");

    EXPECT_DEATH({
        gleam::CubeGeometry({.depth = 0.0f});
    }, ".*params.depth > 0");

    EXPECT_DEATH({
        gleam::CubeGeometry({.width_segments = 0});
    }, ".*params.width_segments > 0");

    EXPECT_DEATH({
        gleam::CubeGeometry({.height_segments = 0});
    }, ".*params.height_segments > 0");

    EXPECT_DEATH({
        gleam::CubeGeometry({.depth_segments = 0});
    }, ".*params.depth_segments > 0");
}

#pragma endregion