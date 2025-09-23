<!-- AUTO-GENERATED — do not edit. -->
# PlaneGeometry


Generates a flat 2D plane geometry assignable to any mesh.
`PlaneGeometry` creates a rectangular surface in the X-Y plane, suitable for ground planes, walls, billboards, or UI backgrounds. It supports width and height segmentation for effects like displacement or tesselation.

```cpp
auto geometry = gleam::PlaneGeometry::Create({
    .width = 5.0f,
    .height = 3.0f,
    .width_segments = 2,
    .height_segments = 2
});

auto mesh = gleam::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
my_scene->Add(mesh);
```
