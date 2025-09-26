<!-- AUTO-GENERATED — do not edit. -->
# Texture2D


Represents a 2D texture that can be attached to materials.
While you can instantiate a Texture2D object directly, it is recommended to use the texture loader object to create texture instances:

```cpp
auto MyNode::OnAttached(SharedContextPointer context) -> void override {
  context->texture_loader->LoadAsync(
    "assets/my_texture.tex",
    [this](auto result) {
      if (result) {
        texture_ = result.value();
      } else {
        std::println(stderr, "{}", result.error());
      }
    }
  );
}
```
## Constructors

### `Texture2D()`
Constructs a Texture2D object.

## Properties

<div class="property">
  <div class="definition">
    <span class="name">data</span> <span class="type">std::vector&lt; uint8_t &gt;</span>
  </div>
  <div class="description">
    Underlying texture data.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">height</span> <span class="type">unsigned</span>
  </div>
  <div class="description">
    Height in pixels.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">width</span> <span class="type">unsigned</span>
  </div>
  <div class="description">
    Width in pixels.
  </div>
</div>

## Functions

### `GetTransform()`
  - Returns the transformation matrix for UV mapping.
### `GetType()`
  - Returns texture type.
### `OffsetX()`
  - Sets texture offset on the X-axis.
### `OffsetY()`
  - Sets texture offset on the Y-axis.
### `Rotate()`
  - Sets rotation angle.
### `Scale()`
  - Sets uniform scale.
### `Create()`
  - Creates a shared pointer to a Texture2D object.
