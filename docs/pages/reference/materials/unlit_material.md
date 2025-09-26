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
## Constructors

### `UnlitMaterial()`
Constructs a UnlitMaterial object.

## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">albedo_map</span> <span class="type">std::shared_ptr&lt;Texture2D&gt;</span>
  ```cpp
  std::shared_ptr<Texture2D> albedo_map { nullptr }
  ```
  </div>
  <div class="description">
    Albedo (base color) map, optionally containing an alpha channel.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">alpha_map</span> <span class="type">std::shared_ptr&lt;Texture2D&gt;</span>
  ```cpp
  std::shared_ptr<Texture2D> alpha_map { nullptr }
  ```
  </div>
  <div class="description">
    Alpha map that controls the opacity across the surface.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">color</span> <span class="type">Color</span>
  ```cpp
  Color color { 0xFFFFFF }
  ```
  </div>
  <div class="description">
    Color of the material.
  </div>
</div>

## Functions

### `GetType()`
  - Returns material type.
### `Create()`
  - Creates a shared pointer to a UnlitMaterial object.
