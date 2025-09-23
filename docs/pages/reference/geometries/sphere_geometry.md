<!-- AUTO-GENERATED — do not edit. -->
# SphereGeometry


Generates a sphere geometry assignable to any mesh.
`SphereGeometry` creates a UV sphere composed of triangles, configurable via radius, width segments (longitude), and height segments (latitude). It’s useful for rendering planets, lighting probes, collision volumes, or decorative primitives.

```cpp
auto geometry = gleam::SphereGeometry::Create({
    .radius = 1.5f,
    .width_segments = 48,
    .height_segments = 24
});

auto mesh = gleam::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
my_scene->Add(mesh);
```
