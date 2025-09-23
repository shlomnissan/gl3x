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
