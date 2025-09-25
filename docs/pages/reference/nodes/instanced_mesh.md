<!-- AUTO-GENERATED — do not edit. -->
# InstancedMesh


A mesh node that renders many instances of the same geometry efficiently.
`InstancedMesh` draws multiple copies of a single geometry-material pair using per‑instance transforms and optional per‑instance colors. This is ideal for large numbers of similar objects (e.g., vegetation, crowds, particles) with different positions or tints while keeping draw calls low.

Each instance can have:a transform matrix (model matrix)a color (for material tinting)

a transform matrix (model matrix)

a color (for material tinting)

Instances are addressed by zero‑based index in the range `[0, Count())`.

```cpp
const auto geometry = BoxGeometry::Create({1.0f, 1.0f, 1.0f});
const auto material = PhongMaterial::Create(0xFFFFFF);

auto boxes = gleam::InstancedMesh::Create(geometry, material, 2500);

for (auto i = 0; i < 50; ++i) {
     for (auto j = 0; j < 50; ++j) {
         auto t = Transform3 {};
         t.SetPosition({i * 2.0f - 49.0f, j * 2.0f - 49.0f, 0.0f});
         boxes->SetTransformAt(j * 50 + i, t);
     }
}

scene->Add(boxes);
```

Out-of-range indices are invalid and result in undefined behavior.Frustum culling is performed once per draw call using a single bounding sphere that encloses all instances (cluster-level culling).

Out-of-range indices are invalid and result in undefined behavior.

Frustum culling is performed once per draw call using a single bounding sphere that encloses all instances (cluster-level culling).
## Constructors

### `InstancedMesh()`
Constructs an instanced mesh.

## Functions

### `BoundingBox()`
  - Returns the instanced mesh cluster bounding box.
### `BoundingSphere()`
  - Returns the instanced mesh cluster bounding sphere.
### `Count()`
  - Returns the number of instances in this mesh.
### `GetColorAt()`
  - Returns the color assigned to a specific instance.
### `GetNodeType()`
  - Returns node type.
### `GetTransformAt()`
  - Returns the transform assigned to a specific instance.
### `SetColorAt()`
  - Sets the color for a specific instance.
### `SetTransformAt()`
  - Sets the model transform for a specific instance.
### `SetTransformAt()`
  - Sets the model transform for a specific instance from a Transform3.
### `Create()`
  - Creates a shared pointer to an InstancedMesh object.
