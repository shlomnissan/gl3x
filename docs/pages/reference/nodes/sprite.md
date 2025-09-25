<!-- AUTO-GENERATED — do not edit. -->
# Sprite


Billboarded quad that always faces the active camera.
Sprite is a flat, unit-sized quad oriented toward the camera at all times. It is usually textured (often with transparency) and exposes the minimal Renderable interface so it can be submitted to the renderer.

Common use cases include particles, labels, icons, and world-space markers.

```cpp
auto MyNode::OnAttached(SharedContextPointer context) -> void override {
  context->texture_loader->LoadAsync(
    "assets/sprite.tex",
    [this](auto result) {
      if (result) {
        auto mat = gleam::SpriteMaterial::Create();
        mat->albedo_map = result.value();
        auto sprite = Sprite::Create(mat);
        sprite->SetScale(0.5f);
        Add(sprite);
      } else {
        std::println(stderr, "{}", result.error());
      }
    }
  );
}
```
## Constructors

### `Sprite()`
Constructs a sprite with an optional material.

## Properties

- `Vector2 anchor`
   - Default value: `0.5f, 0.5f`
  - Normalized anchor point inside the sprite.

- `float rotation`
   - Default value: `0.0f`
  - View-space rotation angle in radians applied to the sprite.

## Functions

### `GetMaterial()`
  - Returns the material associated with the sprite.
### `GetNodeType()`
  - Returns node type.
### `SetMaterial()`
  - Sets the material used to render the sprite.
### `Create()`
  - Creates a shared pointer to a Sprite object with material.
