<!-- AUTO-GENERATED — do not edit. -->
# ShaderMaterial


Represents a material rendered with custom shaders.
This material allows rendering with user-defined GLSL shaders. It is suitable for advanced effects, custom lighting, and any scenario requiring programmable control over the rendering pipeline.

```cpp
auto material = gleam::ShaderMaterial::Create({
  vertex_shader_str,
  fragment_shader_str,
  {
    // custom uniforms
    {"u_Time", 0.0f},
    {"u_Resolution", Vector2::Zero }
  }
});

auto mesh = gleam::Mesh::Create(geometry, material);
scene->Add(mesh);
```
## Properties

- `std::unordered_map< std::string,UniformValue> uniforms`
  - Stores values for custom uniforms used by the shader.
