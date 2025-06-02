/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/lights/directional_light.hpp"

#include "gleam/materials/flat_material.hpp"
#include "gleam/nodes/mesh.hpp"

namespace gleam {

static constexpr auto debug_mesh_size = 0.5f;

struct DirectionalLight::Impl {
    std::shared_ptr<Mesh> line;
    std::shared_ptr<Mesh> plane;
    std::shared_ptr<FlatMaterial> material;

    auto UpdateDebugMesh(DirectionalLight* self) {
        const auto target_world_pos = self->target != nullptr
            ? self->target->GetWorldPosition()
            : Vector3::Zero();

        plane->LookAt(target_world_pos);
        line->LookAt(target_world_pos);
        material->color = self->color;

        const auto length = (target_world_pos - self->GetWorldPosition()).Length();
        plane->SetScale(debug_mesh_size);
        line->SetScale({1.0f, 1.0f, length});
    }

    auto CreateDebugMesh(DirectionalLight* self) {
        using enum GeometryAttributeType;
        using enum GeometryPrimitiveType;

        material = FlatMaterial::Create();
        material->two_sided = true;
        material->color = self->color;
        material->wireframe = true;
        material->fog = false;

        line = Mesh::Create(Geometry::Create({
            0, 0, 0,
            0, 0, 1
        }), material);
        line->geometry->SetName("directional light line");
        line->geometry->SetAttribute({Position, 3});
        line->geometry->primitive = Lines;
        line->transform_auto_update = false;
        self->Add(line);

        plane = Mesh::Create(Geometry::Create({
            -1,  1, 0,
             1,  1, 0,
             1, -1, 0,
            -1, -1, 0
        }), material);
        plane->geometry->SetName("directional light plane");
        plane->geometry->SetAttribute({Position, 3});
        plane->geometry->primitive = LineLoop;
        plane->transform_auto_update = false;

        self->Add(plane);
        UpdateDebugMesh(self);
    }

    auto RemoveDebugMesh(DirectionalLight* self) {
        if (line != nullptr) self->Remove(line);
        if (plane != nullptr) self->Remove(plane);
        line.reset();
        plane.reset();
        material.reset();
    }
};

DirectionalLight::DirectionalLight(const Parameters& params) :
    Light(params.color, params.intensity),
    target(params.target),
    impl_(std::make_unique<Impl>())
{
    SetName("directional light");
}

auto DirectionalLight::Direction() -> Vector3 {
    if (target != nullptr) {
        return Normalize(GetWorldPosition() - target->GetWorldPosition());
    }
    return Normalize(GetWorldPosition());
}

auto DirectionalLight::SetDebugMode(bool is_debug_mode) -> void {
    if (debug_mode_enabled_ != is_debug_mode) {
        is_debug_mode ?
            impl_->CreateDebugMesh(this) :
            impl_->RemoveDebugMesh(this);
        debug_mode_enabled_ = is_debug_mode;
    }
}

auto DirectionalLight::OnUpdate(float delta) -> void {
    if (debug_mode_enabled_) {
        impl_->UpdateDebugMesh(this);
    }
}

DirectionalLight::~DirectionalLight() = default;

}