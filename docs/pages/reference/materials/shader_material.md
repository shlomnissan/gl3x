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
## Constructors

### `ShaderMaterial()`
Constructs a ShaderMaterial object.

## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">uniforms</span> <span class="type">std::unordered_map&lt; std::string,UniformValue&gt;</span>
  ```cpp
  std::unordered_map< std::string,UniformValue> uniforms 
  ```
  </div>
  <div class="description">
    Stores values for custom uniforms used by the shader.
  </div>
</div>

## Functions

### `GetType()`
  - Returns material type.
### `Create()`
  - Creates a shared pointer to a ShaderMaterial object.
