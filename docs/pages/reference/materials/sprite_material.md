<!-- AUTO-GENERATED — do not edit. -->
# SpriteMaterial


Represents a material for 2D sprites.
`SpriteMaterial` is a lightweight material optimized for rendering camera-facing quads such as UI elements, particles, or font glyphs. It supports a solid color, an optional albedo map, and an optional alpha map for per-pixel transparency.

Unlike physically-based or Phong materials, `SpriteMaterial` is rendered without lighting by default, making it efficient for 2D overlays and screen-space elements.

```cpp
auto material = gleam::SpriteMaterial::Create(0xFFFFFF);
material->albedo_map = texture;

auto sprite = gleam::Sprite::Create(material);
scene->Add(sprite);
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
