// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/geometry/plane_geometry.hpp>

#pragma region Fixtures

class PlaneGeometryTest : public ::testing::Test {
protected:
    engine::PlaneGeometry plane_ {{
        .width = 1.0f,
        .height = 1.0f,
        .width_segments = 2,
        .height_segments = 2
    }};
};

#pragma endregion

#pragma region Constructor

TEST_F(PlaneGeometryTest, ConstructorInitializesVertexData) {
    const auto& verts = plane_.VertexData();

    // 9 attributes, 8 vertices
    EXPECT_EQ(verts.size(), 9 * 8);
}

TEST_F(PlaneGeometryTest, ConstructorInitializesIndexData) {
    const auto& index = plane_.IndexData();

    // 6 indices (2 triangles per sub-plane), 4 sub-planes
    EXPECT_EQ(index.size(), 6 * 4);
}

#pragma endregion

#pragma region Attributes

TEST_F(PlaneGeometryTest, AttributesConfiguredCorrectly) {
    using enum engine::GeometryAttributeType;

    const auto& attrs = plane_.Attributes();

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

TEST(PlaneGeometry, DeathWhenParamsAreSetToZero) {
    EXPECT_DEATH({
        engine::PlaneGeometry({
            .width = 0.0f,
            .height = 4.0f,
            .width_segments = 2,
            .height_segments = 2
        });
    }, ".*params.width > 0");

    EXPECT_DEATH({
        engine::PlaneGeometry({
            .width = 3.0f,
            .height = 0.0f,
            .width_segments = 2,
            .height_segments = 2
        });
    }, ".*params.height > 0");

    EXPECT_DEATH({
        engine::PlaneGeometry({
            .width = 3.0f,
            .height = 4.0f,
            .width_segments = 0,
            .height_segments = 2
        });
    }, ".*params.width_segments > 0");

    EXPECT_DEATH({
        engine::PlaneGeometry({
            .width = 3.0f,
            .height = 4.0f,
            .width_segments = 2,
            .height_segments = 0
        });
    }, ".*params.height_segments > 0");
}

#pragma endregion