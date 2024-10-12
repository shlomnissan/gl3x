// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/color.hpp"
#include "engine/textures/texture_2d.hpp"

#include "core/identity.hpp"

#include <string>
#include <memory>

namespace engine {

enum class MaterialType {
    kFlatMaterial,
    kPhongMaterial
};

class Material : public Identity {
public:
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

}