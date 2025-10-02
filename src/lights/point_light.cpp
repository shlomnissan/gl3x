/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/lights/point_light.hpp"

#include "gl3x/geometries/sphere_geometry.hpp"
#include "gl3x/materials/unlit_material.hpp"
#include "gl3x/nodes/mesh.hpp"

namespace gleam {

static constexpr auto debug_mesh_size = 0.2f;

struct PointLight::Impl {
    std::shared_ptr<Mesh> sphere;
    std::shared_ptr<UnlitMaterial> material;

    auto CreateDebugMesh(PointLight* self) -> void {
        material = UnlitMaterial::Create();
        material->two_sided = true;
        material->color = self->color;
        material->wireframe = true;
        material->fog = false;
        sphere = Mesh::Create(SphereGeometry::Create({
            .radius = 1,
            .width_segments = 4,
            .height_segments = 2
        }), material);

        self->Add(sphere);
        UpdateDebugMesh(self);
    }

    auto UpdateDebugMesh(PointLight* self) -> void {
        sphere->SetScale(debug_mesh_size);
        material->color = self->color;
    }

    auto RemoveDebugMesh(PointLight* self) -> void {
        if (sphere != nullptr) self->Remove(sphere);
        sphere.reset();
        material.reset();
    }
};

PointLight::PointLight(const Parameters& params)  :
    Light(params.color, params.intensity),
    attenuation(params.attenuation),
    impl_(std::make_unique<Impl>())
{
    SetName("point light");
}

auto PointLight::SetDebugMode(bool is_debug_mode) -> void {
    if (debug_mode_enabled_ != is_debug_mode) {
        is_debug_mode
        ? impl_->CreateDebugMesh(this)
        : impl_->RemoveDebugMesh(this);
        debug_mode_enabled_ = is_debug_mode;
    }
}

auto PointLight::OnUpdate(float delta) -> void {
    if (debug_mode_enabled_) {
        impl_->UpdateDebugMesh(this);
    }
}

PointLight::~PointLight() = default;

}