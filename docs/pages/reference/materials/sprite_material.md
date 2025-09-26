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
## Constructors

### `SpriteMaterial()`
Constructs a SpriteMaterial object.

## Properties

<div class="property">
  <div class="definition">
    <span class="name">albedo_map</span> <span class="type">std::shared_ptr&lt;Texture2D&gt;</span>
  </div>
  <div class="description">
    Albedo (base color) map, optionally containing an alpha channel.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">alpha_map</span> <span class="type">std::shared_ptr&lt;Texture2D&gt;</span>
  </div>
  <div class="description">
    Alpha map that controls the opacity across the surface.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">color</span> <span class="type">Color</span>
  </div>
  <div class="description">
    Color of the material.
  </div>
</div>

## Functions

### `GetType()`
  - Returns material type.
### `Create()`
  - Creates a shared pointer to a SpriteMaterial object.
