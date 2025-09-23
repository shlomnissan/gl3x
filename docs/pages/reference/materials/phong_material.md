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
