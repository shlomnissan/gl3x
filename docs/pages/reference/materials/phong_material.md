<!-- AUTO-GENERATED — do not edit. -->
# PhongMaterial


Represents a material for shiny surfaces with specular highlights.
This material implements the Blinn-Phong model for calculating reflectance. It is suitable for rendering glossy or metallic surfaces that require highlights and simulate light interaction.

```cpp
auto material = gleam::PhongMaterial::Create(0x049EF4);
material->specular = {0.3f, 0.3, 0.3f}
material->shininess = 32.0f;
material->albedo_map = texture;

auto mesh = gleam::Mesh::Create(geometry, material);
scene->Add(mesh);
```
## Constructors

### `PhongMaterial()`
Constructs a PhongMaterial object.

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

<div class="property">
  <div class="definition">

  ### <span class="name">shininess</span> <span class="type">float</span>
  ```cpp
  float shininess { 32.0f }
  ```
  </div>
  <div class="description">
    How shiny the specular highlight is; a higher value gives a sharper highlight.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">specular</span> <span class="type">Color</span>
  ```cpp
  Color specular { 0x111111 }
  ```
  </div>
  <div class="description">
    Specular color of the material.
  </div>
</div>

## Functions

### `GetType()`
  - Returns material type.
### `Create()`
  - Creates a shared pointer to a PhongMaterial object.
