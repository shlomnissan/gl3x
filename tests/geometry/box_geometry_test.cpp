// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/geometry/box_geometry.hpp>

#pragma region Fixtures

class BoxGeometryTest : public ::testing::Test {
protected:
    engine::BoxGeometry box_ {{
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

TEST_F(BoxGeometryTest, ConstructorInitializesVertexData) {
    const auto& verts = box_.VertexData();

    // 9 attributes, 8 vertices, 6 planes
    EXPECT_EQ(verts.size(), 9 * 8 * 6);
}

TEST_F(BoxGeometryTest, ConstructorInitializesIndexData) {
    const auto& index = box_.IndexData();

    // 6 indices (2 triangles per sub-plane), 4 sub-planes, 6 faces
    EXPECT_EQ(index.size(), 6 * 4 * 6);
}

#pragma endregion

#pragma region Attributes

TEST_F(BoxGeometryTest, AttributesConfiguredCorrectly) {
    using enum engine::GeometryAttributeType;

    const auto& attrs = box_.Attributes();

    EXPECT_EQ(attrs.size(), 3);

    EXPECT_EQ(attrs[0].type, kPosition);
    EXPECT_EQ(attrs[0].item_size, 3u);
    EXPECT_EQ(attrs[0].offset, 0u);

    EXPECT_EQ(attrs[1].type, kNormal);
    EXPECT_EQ(attrs[1].item_size, 3u);
    EXPECT_EQ(attrs[1].offset, 3u);

    EXPECT_EQ(attrs[2].type, kUV);
    EXPECT_EQ(attrs[2].item_size, 2u);
    EXPECT_EQ(attrs[2].offset, 6u);
}

#pragma endregion

#pragma region Assertions

TEST(BoxGeometry, DeathWhenParamsAreSetToZero) {
    EXPECT_DEATH({
        engine::BoxGeometry({
            .width = 0.0f,
            .height = 1.0f,
            .depth = 1.0f,
            .width_segments = 2,
            .height_segments = 2,
            .depth_segments = 2
        });
    }, ".*params.width > 0");

    EXPECT_DEATH({
        engine::BoxGeometry({
            .width = 1.0f,
            .height = 0.0f,
            .depth = 1.0f,
            .width_segments = 2,
            .height_segments = 2,
            .depth_segments = 2
        });
    }, ".*params.height > 0");

    EXPECT_DEATH({
        engine::BoxGeometry({
            .width = 1.0f,
            .height = 1.0f,
            .depth = 0.0f,
            .width_segments = 2,
            .height_segments = 2,
            .depth_segments = 2
        });
    }, ".*params.depth > 0");

    EXPECT_DEATH({
        engine::BoxGeometry({
            .width = 1.0f,
            .height = 1.0f,
            .depth = 1.0f,
            .width_segments = 0,
            .height_segments = 2,
            .depth_segments = 2
        });
    }, ".*params.width_segments > 0");

    EXPECT_DEATH({
        engine::BoxGeometry({
            .width = 1.0f,
            .height = 1.0f,
            .depth = 1.0f,
            .width_segments = 2,
            .height_segments = 0,
            .depth_segments = 2
        });
    }, ".*params.height_segments > 0");

    EXPECT_DEATH({
        engine::BoxGeometry({
            .width = 1.0f,
            .height = 1.0f,
            .depth = 1.0f,
            .width_segments = 2,
            .height_segments = 2,
            .depth_segments = 0
        });
    }, ".*params.depth_segments > 0");
}

#pragma endregion