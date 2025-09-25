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

- `std::vector< uint8_t > data`
  - Underlying texture data.

- `unsigned height`
  - Height in pixels.

- `unsigned width`
  - Width in pixels.

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
