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
## Constructors

### `Geometry()`
Constructs a Geometry object with vertex and index data.

## Properties

<div class="property">
  <div class="definition">
    <span class="name">primitive</span> <span class="type">GeometryPrimitiveType</span>
  </div>
  <div class="description">
    Primitive type used for rendering.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">renderer_id</span> <span class="type">unsigned int</span>
  </div>
  <div class="description">
    GPU renderer identifier. Used internally by the renderer.
  </div>
</div>

## Functions

### `Attributes()`
  - Returns all defined vertex attributes.
### `BoundingBox()`
  - Returns the geometry's bounding box (computed on demand).
### `BoundingSphere()`
  - Returns the geometry's bounding sphere (computed on demand).
### `HasAttribute()`
  - Returns whether a given attribute type is present.
### `IndexCount()`
  - Returns the number of indices.
### `IndexData()`
  - Returns raw index data.
### `SetAttribute()`
  - Adds a vertex attribute.
### `Stride()`
  - Returns the vertex stride in floats (sum of all active attribute sizes).
### `VertexCount()`
  - Returns the number of vertices (size / stride).
### `VertexData()`
  - Returns raw vertex data.
### `Create()`
  - Creates a shared pointer to a Geometry object.
### `Create()`
  - Creates a shared pointer to a Geometry object with vertex and index data.
