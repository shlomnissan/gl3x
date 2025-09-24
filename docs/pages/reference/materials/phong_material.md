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

- `float shininess`
   - Default value: `32.0f`
  - How shiny the specular highlight is; a higher value gives a sharper highlight.

- `Color specular`
   - Default value: `0x111111`
  - Specular color of the material.
