// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/color.hpp"
#include "engine/textures/texture_2d.hpp"

#include "core/identity.hpp"

#include <memory>
#include <optional>
#include <string>

namespace engine {

#pragma region Types

enum class MaterialType {
    kFlatMaterial,
    kPhongMaterial
};

struct PolygonOffset {
    float factor {0.0f};
    float units {0.0f};
};

#pragma endregion

class Material : public Identity {
public:
    std::optional<PolygonOffset> polygon_offset;

    bool cull_backfaces {true};
    bool supports_lights {false};

    Material() = default;

    Material(const Material&) = delete;
    Material(Material&&) = delete;
    auto operator=(const Material&) -> Material& = delete;
    auto operator=(Material&&) -> Material& = delete;

    virtual auto Type() const -> MaterialType = 0;

    template<class T> requires std::is_base_of_v<Material, T>
    [[nodiscard]] auto Is() const {
        return dynamic_cast<const T*>(this) != nullptr;
    }

    template<class T> requires std::is_base_of_v<Material, T>
    [[nodiscard]] auto As() {
        return dynamic_cast<T*>(this);
    }

    template<class T> requires std::is_base_of_v<Material, T>
    [[nodiscard]] auto As() const {
        return dynamic_cast<const T*>(this);
    }

    virtual ~Material() = default;
};

#pragma region Material Attributes

struct MaterialWithColor : virtual Material {
    Color color;

    explicit MaterialWithColor(const Color& color)
      : color(color) {}
};

struct MaterialWithTextureMap : virtual Material {
    std::shared_ptr<Texture2D> texture_map;

    explicit MaterialWithTextureMap(std::shared_ptr<Texture2D> texture)
      : texture_map(texture) {}
};

#pragma endregion

#pragma region Utility Functions

static auto MaterialTypeToString(MaterialType type) {
    switch(type) {
        case MaterialType::kFlatMaterial:
            return "flat";
        case MaterialType::kPhongMaterial:
            return "phong";
        default:
            return "unkonwn";
    }
}

#pragma endregion

}