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
## Properties

- `std::shared_ptr<Texture2D> albedo_map`
   - Default value: `nullptr`
  - Albedo (base color) map, optionally containing an alpha channel.

- `std::shared_ptr<Texture2D> alpha_map`
   - Default value: `nullptr`
  - Alpha map that controls the opacity across the surface.

- `Color color`
   - Default value: `0xFFFFFF`
  - Color of the material.
