<!-- AUTO-GENERATED — do not edit. -->
# Geometry


Represents GPU-ready geometry data including vertex and index buffers.
The `Geometry` class is the fundamental unit of renderable mesh data in Gleam. It contains raw vertex data, optional indices, and layout metadata. Geometry can be rendered using different primitive types (triangles, lines, etc.) and may expose bounds such as bounding boxes and spheres for culling or physics.

Instances are typically created using the static `Create()` methods and then configured with attribute metadata via `SetAttribute`.

```cpp
auto geometry = gleam::Geometry::Create({
  0.5f, -0.5f, 0.0f,
  0.0f,  0.5f, 0.0f,
 -0.5f, -0.5f, 0.0f,
});

geometry->SetAttribute({GeometryAttributeType::Position, 3});
Add(Mesh::Create(geometry, UnlitMaterial::Create(0xFF0133)));
```
## Properties

- `GeometryPrimitiveType primitive`
   - Default value: `GeometryPrimitiveType::Triangles`
  - Primitive type used for rendering.

- `unsigned int renderer_id`
   - Default value: `0`
  - GPU renderer identifier. Used internally by the renderer.
