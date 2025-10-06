/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/core/identity.hpp"
#include "vglx/math/color.hpp"

#include <memory>
#include <optional>
#include <string>

namespace gl3x {

/**
 * @brief Represents available material types.
 * @ingroup MaterialsGroup
 */
enum class MaterialType {
    PhongMaterial,
    ShaderMaterial,
    SpriteMaterial,
    UnlitMaterial,
    Length,
};

/**
 * @brief Represents available blending modes.
 * @ingroup MaterialsGroup
 */
enum class Blending {
    None,
    Normal,
    Additive,
    Subtractive,
    Multiply
};

/**
 * @brief Abstract base class for material types.
 *
 * Not intended for direct use.
 *
 * @ingroup MaterialsGroup
 */
class VGLX_EXPORT Material : public Identity {
public:
    /// @brief Value in the range of `0.0` - `1.0` indicating how transparent the material is.
    float opacity {1.0f};

    /// @brief Sets the polygon offset factor.
    float polygon_offset_factor {0.0f};

    /// @brief Sets the polygon offset units.
    float polygon_offset_units {0.0f};

    /// @brief Enables scene fog for this material.
    bool fog {true};

    /// @brief Enables rendering both front and back faces of polygons.
    bool two_sided {false};

    /// @brief Enables depth testing.
    bool depth_test {true};

    /// @brief Enables wireframe rendering.
    bool wireframe {false};

    /// @brief Enables transparency.
    bool transparent {false};

    /// @brief Enables flat shading.
    bool flat_shaded {false};

    /// @brief Enables visibility.
    bool visible {true};

    /// @brief Blending mode used for rendering this material.
    Blending blending {Blending::Normal};

    /**
     * @brief Returns material type.
     *
     * @return MaterialType
     */
    [[nodiscard]] virtual auto GetType() const -> MaterialType = 0;

    /**
     * @brief Converts material type enum value to string.
     *
     * @param type MaterialType enum value.
     * @return String representation of material type.
     */
    [[nodiscard]] inline static auto TypeToString(MaterialType type) {
        switch(type) {
            case MaterialType::PhongMaterial:
                return "phong_material";
            case MaterialType::ShaderMaterial:
                return "shader_material";
            case MaterialType::SpriteMaterial:
                return "sprite_material";
            case MaterialType::UnlitMaterial:
                return "unlit_material";
            default:
                return "unkonwn";
        }
    }

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Material() = default;
};

}