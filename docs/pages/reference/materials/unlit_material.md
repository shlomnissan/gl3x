<!-- AUTO-GENERATED — do not edit. -->
# UnlitMaterial


Represents a material for surfaces that are not affected by lights.
This material is used to render objects with uniform color or texture, without any lighting calculations. It is ideal for UI elements, 2D overlays, or wireframes where shading is not desired.

```cpp
auto material = gleam::UnlitMaterial::Create(0x049EF4);
material->albedo_map = texture;

auto mesh = gleam::Mesh::Create(geometry, material);
scene->Add(mesh);
```
