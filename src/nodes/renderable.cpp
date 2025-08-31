/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/renderable.hpp"

#include "gleam/nodes/mesh.hpp"

#include "utilities/logger.hpp"

namespace gleam {

auto Renderable::CanRender(Renderable* r) -> bool {
    const auto level = LogLevel::Error;
    const auto geometry = r->GetGeometry();
    const auto material = r->GetMaterial();
    const auto mat_type = material->GetType();
    const auto node_type = r->GetNodeType();

    if (geometry == nullptr) {
        Logger::Log(level, "Skipped rendering a node with invalid geometry {}", *r);
        return false;
    }

    if (geometry->Disposed()) {
        Logger::Log(level, "Skipped rendering a node with disposed geometry {}", *r);
        return false;
    }

    if (geometry->VertexData().empty()) {
        Logger::Log(level, "Skipped node with no geometry data {}", *r);
        return false;
    }

    if (geometry->Attributes().empty()) {
        Logger::Log(level, "Skipped node with no vertex attributes {}", *r);
        return false;
    }

    if (material == nullptr) {
        Logger::Log(level, "Skipped node with invalid material {}", *r);
        return false;
    }

    if (node_type == NodeType::SpriteNode && mat_type != MaterialType::SpriteMaterial) {
        Logger::Log(level, "Skipped sprite with non-sprite material {}", *r);
        return false;
    }

    if (mat_type == MaterialType::SpriteMaterial && node_type != NodeType::SpriteNode) {
        Logger::Log(level, "Skipped non-sprite node with sprite material {}", *r);
        return false;
    }

    return true;
}

auto Renderable::IsInFrustum(Renderable* r, const Frustum& frustum) -> bool {
    if (r->GetNodeType() == NodeType::SpriteNode) return true;

    auto mesh = static_cast<Mesh*>(r);
    auto bounding_sphere = mesh->BoundingSphere();
    bounding_sphere.ApplyTransform(mesh->GetWorldTransform());

    return frustum.IntersectsWithSphere(bounding_sphere);
}

auto Renderable::IsMeshType(Renderable* r) -> bool {
    return r->GetNodeType() == NodeType::MeshNode ||
           r->GetNodeType() == NodeType::InstancedMeshNode;
}

}