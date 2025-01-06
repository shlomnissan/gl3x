// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/math/color.hpp"
#include "engine/textures/texture_2d.hpp"

#include "core/identity.hpp"

#include <memory>
#include <optional>
#include <string>

namespace engine {

/**
 * @brief The type of material.
 */
enum class MaterialType {
    FlatMaterial,
    PhongMaterial
};

/**
 * @brief Structure to define polygon offset parameters.
 */
struct ENGINE_EXPORT PolygonOffset {
    /// @brief Scales the maximum depth slope of a polygon for depth offset.
    float factor {0.0f};
    /// @brief Specify a constant depth offset.
    float units {0.0f};
};

/**
 * @brief Abstract base class for materials.
 */
class ENGINE_EXPORT Material : public Identity {
public:
    /// @brief Optional polygon offset to prevent z-fighting.
    std::optional<PolygonOffset> polygon_offset;

    /// @brief The opacity of the material.
    float opacity {1.0f};

    /// @brief Flag indicating whether the material is affected by fog.
    bool fog {true};

    /// @brief Flag indicating whether backfaces should be culled.
    bool cull_backfaces {true};

    /// @brief Flag indicating whether the face orientation should be inverted.
    bool invert_face_orientation {false};

    /// @brief Flag indicating whether the material should be rendered in wireframe mode.
    bool wireframe {false};

    /// @brief Flag indicating whether the material is transparent.
    bool transparent {false};

    /**
     * @brief Default constructor.
     */
    Material() = default;

    /**
     * @brief Retrieves the type of the material.
     *
     * @return The type of the material.
     */
    virtual auto Type() const -> MaterialType = 0;

    /**
     * @brief Checks if the material is of the specified type.
     *
     * @tparam T The type of material to check.
     * @return `true` if the material is of the specified type, `false` otherwise.
     */
    template<class T> requires std::is_base_of_v<Material, T>
    [[nodiscard]] auto Is() const {
        return dynamic_cast<const T*>(this) != nullptr;
    }

    /**
     * @brief Casts the material to the specified type.
     *
     * @tparam T The type of material to cast to.
     * @return A pointer to the material cast to the specified type.
     */
    template<class T> requires std::is_base_of_v<Material, T>
    [[nodiscard]] auto As() {
        return dynamic_cast<T*>(this);
    }

    /**
     * @brief Casts the material to the specified type (const version).
     *
     * @tparam T The type of material to cast to.
     * @return A pointer to the material cast to the specified type.
     */
    template<class T> requires std::is_base_of_v<Material, T>
    [[nodiscard]] auto As() const {
        return dynamic_cast<const T*>(this);
    }

    /**
     * @brief Converts a material type to a string.
     *
     * @param type The material type to convert.
     * @return The string representation of the material type.
     */
    [[nodiscard]] inline static auto TypeToString(MaterialType type) {
        switch(type) {
            case MaterialType::FlatMaterial:
                return "flat";
            case MaterialType::PhongMaterial:
                return "phong";
            default:
                return "unkonwn";
        }
    }

    /**
     * @brief Default destructor.
     */
    virtual ~Material() = default;
};

}