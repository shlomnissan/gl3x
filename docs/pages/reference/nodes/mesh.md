<!-- AUTO-GENERATED — do not edit. -->
# Mesh


Renderable node that draws a Geometry with a Material.
Mesh is a scene node that owns a geometry and a material and exposes them through the Renderable interface so the renderer can process and draw it.

An optional wireframe geometry can be provided for debug rendering.

```cpp
auto geometry = gleam::BoxGeometry::Create();
auto material = gleam::UnlitMaterial::Create(0x00FFAA);
auto mesh = gleam::Mesh::Create(geometry, material);
my_scene->Add(mesh);
```
