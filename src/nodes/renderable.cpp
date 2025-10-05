/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/nodes/renderable.hpp"

#include "gl3x/nodes/mesh.hpp"

#include "utilities/logger.hpp"

namespace gl3x {

auto Renderable::BoundingBox() -> Box3 {
    return GetGeometry()->BoundingBox();
}

auto Renderable::BoundingSphere() -> Sphere {
    return GetGeometry()->BoundingSphere();
}

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

    if (!geometry->HasAttribute(VertexAttributeType::Position)) {
        Logger::Log(level, "Skipped node with no vertex positions {}", *r);
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

auto Renderable::InFrustum(Renderable* r, const Frustum& frustum) -> bool {
    auto bounding_sphere = r->BoundingSphere();
    bounding_sphere.ApplyTransform(r->GetWorldTransform());
    return frustum.IntersectsWithSphere(bounding_sphere);
}

auto Renderable::IsMeshType(Renderable* r) -> bool {
    return r->GetNodeType() == NodeType::MeshNode ||
           r->GetNodeType() == NodeType::InstancedMeshNode;
}

}