// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/lights/spot_light.hpp"

#include <cmath>
#include <vector>

namespace engine {

auto SpotLight::Direction() -> Vector3 {
    if (target != nullptr) {
        return Normalize(GetWorldPosition() - target->GetWorldPosition());
    }
    return Normalize(GetWorldPosition());
}

auto SpotLight::SetDebugMode(bool is_debug_mode) -> void {
    if (debug_mode_enabled != is_debug_mode) {
        if (is_debug_mode) {
            CreateDebugMesh();
        } else {
            Remove(debug_mesh_cone_);
            debug_mesh_cone_.reset();
        }
        debug_mode_enabled = is_debug_mode;
    }
}

auto SpotLight::OnUpdate(float delta) -> void {
    if (debug_mode_enabled) {
        UpdateDebugMesh();
    }
}

auto SpotLight::CreateDebugMesh() -> void {
    using enum GeometryAttributeType;
    using enum GeometryPrimitiveType;

    debug_mesh_material_ = FlatMaterial::Create();
    debug_mesh_material_->two_sided = true;
    debug_mesh_material_->color = color;
    debug_mesh_material_->wireframe = true;
    debug_mesh_material_->fog = false;

    // lines for the cone
    auto points = std::vector<float> {
        0, 0, 0,  0,  0, 1,
        0, 0, 0,  1,  0, 1,
        0, 0, 0, -1,  0, 1,
        0, 0, 0,  0,  1, 1,
        0, 0, 0,  0, -1, 1,
    };

    // circle for the cone base
    static constexpr auto circle_line_segments = 64;
    for (unsigned i = 0, j = 1, l = circle_line_segments; i < l; i++, j++) {
        const auto p1 = (static_cast<float>(i) / static_cast<float>(l)) * math::two_pi;
        const auto p2 = (static_cast<float>(j) / static_cast<float>(l)) * math::two_pi;
        points.insert(points.end(), {
            std::cos(p1), std::sin(p1), 1.0f,
            std::cos(p2), std::sin(p2), 1.0f
        });
    }

    debug_mesh_cone_ = Mesh::Create(Geometry::Create(points), debug_mesh_material_);
    debug_mesh_cone_->geometry->SetName("directional light line");
    debug_mesh_cone_->geometry->SetAttribute({Position, 3});
    debug_mesh_cone_->geometry->primitive = Lines;
    debug_mesh_cone_->transform_auto_update = false;

    Add(debug_mesh_cone_);
    UpdateDebugMesh();
}

auto SpotLight::UpdateDebugMesh() -> void {
    const auto target_world_pos = target != nullptr
        ? target->GetWorldPosition()
        : Vector3::Zero();

    const auto cone_length = (target_world_pos - this->GetWorldPosition()).Length() + 1.0f;
    const auto cone_width = std::tan(angle) * cone_length;

    debug_mesh_cone_->LookAt(target_world_pos);
    debug_mesh_cone_->SetScale({cone_width, cone_width, cone_length});
    debug_mesh_material_->color = color;
}

}