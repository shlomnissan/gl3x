// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include <engine/geometry/plane_geometry.hpp>

#pragma region Constructor

TEST(PlaneGeometry, ConstructorInitializesVertexData) {
    const auto plane = engine::PlaneGeometry {{
        .width = 10.f,
        .height = 4.0f,
        .width_segments = 2,
        .height_segments = 2
    }};

    const auto& verts = plane.VertexData();

    EXPECT_EQ(verts.size(), 9 * 8);     // 8 vertices with 9 attributes each
    EXPECT_FLOAT_EQ(verts[0], -5.0f);   // first vertex, pos x
    EXPECT_FLOAT_EQ(verts[1],  2.0f);   // first vertex, pos y
    EXPECT_FLOAT_EQ(verts[2],  0.0f);   // first vertex, pos z
    EXPECT_FLOAT_EQ(verts[3],  0.0f);   // first vertex, normal x
    EXPECT_FLOAT_EQ(verts[4],  0.0f);   // first vertex, normal y
    EXPECT_FLOAT_EQ(verts[5],  1.0f);   // first vertex, normal z
    EXPECT_FLOAT_EQ(verts[6],  0.0f);   // first vertex, u
    EXPECT_FLOAT_EQ(verts[7],  1.0f);   // first vertex, v
}

TEST(PlaneGeometry, ConstructorInitializesIndexData) {
    const auto plane = engine::PlaneGeometry {{
        .width = 10.f,
        .height = 4.0f,
        .width_segments = 2,
        .height_segments = 2
    }};

    const auto& index = plane.IndexData();

    EXPECT_EQ(index.size(), 6 * 4); // 4 quads with 6 indices each
    EXPECT_EQ(index[0], 0u);
    EXPECT_EQ(index[1], 3u);
    EXPECT_EQ(index[2], 1u);
    EXPECT_EQ(index[3], 3u);
    EXPECT_EQ(index[4], 4u);
    EXPECT_EQ(index[5], 1u);
}

#pragma endregion

#pragma region Attributes

TEST(PlaneGeometry, AttributesConfiguredCorrectly) {
    using enum engine::GeometryAttributeType;

    const auto plane = engine::PlaneGeometry {{
        .width = 10.f,
        .height = 4.0f,
        .width_segments = 2,
        .height_segments = 2
    }};

    const auto& attrs = plane.Attributes();

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

#pragma region Edge Cases

TEST(PlaneGeometry, ParamsAreNotZero) {
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