/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>

#include <gl3x/geometries/sphere_geometry.hpp>

#pragma region Fixtures

class SphereGeometryTest : public ::testing::Test {
protected:
    gleam::SphereGeometry sphere_ {{
        .width_segments = 3,
        .height_segments = 2,
    }};
};

#pragma endregion

#pragma region Constructor

TEST_F(SphereGeometryTest, ConstructorInitializesVertexData) {
    const auto& verts = sphere_.VertexData();

    // 8 values per vertex, 12 vertices
    EXPECT_EQ(verts.size(), 8 * 12);
}

TEST_F(SphereGeometryTest, ConstructorInitializesIndexData) {
    const auto& index = sphere_.IndexData();

    // 36 indices (6 quads * 2 triangles)
    EXPECT_EQ(index.size(), 6 * 6);
}

TEST_F(SphereGeometryTest, ConstructorInitializesName) {
    EXPECT_EQ(sphere_.Name(), "sphere geometry");
}

#pragma endregion

#pragma region Attributes

TEST_F(SphereGeometryTest, AttributesConfiguredCorrectly) {
    using enum gleam::VertexAttributeType;

    const auto& attrs = sphere_.Attributes();

    EXPECT_EQ(attrs[0].type, Position);
    EXPECT_EQ(attrs[0].item_size, 3u);
    EXPECT_EQ(attrs[1].type, Normal);
    EXPECT_EQ(attrs[1].item_size, 3u);
    EXPECT_EQ(attrs[2].type, UV);
    EXPECT_EQ(attrs[2].item_size, 2u);
}

#pragma endregion

#pragma region Assertions

TEST(SphereGeometry, DeathWhenParamsAreInvalid) {
    EXPECT_DEATH({
        gleam::SphereGeometry({.radius = 0.0f});
    }, ".*params.radius > 0.0f");

    EXPECT_DEATH({
        gleam::SphereGeometry({.width_segments = 2});
    }, ".params.width_segments >= 3");

    EXPECT_DEATH({
        gleam::SphereGeometry({.height_segments = 1});
    }, ".params.height_segments >= 2");
}

#pragma endregion