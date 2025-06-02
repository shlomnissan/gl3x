/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>

#include <gleam/geometries/sphere_geometry.hpp>

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

    // 18 indices (6 triangles)
    EXPECT_EQ(index.size(), 6 * 3);
}

TEST_F(SphereGeometryTest, ConstructorInitializesName) {
    EXPECT_EQ(sphere_.Name(), "sphere geometry");
}

#pragma endregion

#pragma region Attributes

TEST_F(SphereGeometryTest, AttributesConfiguredCorrectly) {
    using enum gleam::GeometryAttributeType;

    const auto& attrs = sphere_.Attributes();

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

    EXPECT_DEATH({
        gleam::SphereGeometry({.phi_start = -0.1f});
    }, ".*params.phi_start >= 0.0f");

    EXPECT_DEATH({
        gleam::SphereGeometry({.phi_length = -0.1f});
    }, ".*params.phi_length >= 0.0f");

    EXPECT_DEATH({
        gleam::SphereGeometry({.theta_start = -0.1f});
    }, ".*params.theta_start >= 0.0f");

    EXPECT_DEATH({
        gleam::SphereGeometry({.theta_length = -0.1f});
    }, ".*params.theta_length >= 0.0f");
}

#pragma endregion