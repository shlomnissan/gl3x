<!-- AUTO-GENERATED — do not edit. -->
# DirectionalLight


Represents a light that gets emitted in a specific direction.
This light will behave as though it is infinitely far away and the rays produced from it are all parallel. The common use case for this is to simulate daylight; the sun is far enough away that its position can be considered to be infinite, and all light rays coming from it are parallel.

```cpp
auto directional_light = gleam::DirectionalLight::Create({
  .color = 0xFFFFFF,
  .intensity = 1.0f,
  .target = nullptr
});
```

When the target parameter is set to `nullptr` the light points to (0, 0, 0).
## Constructors

### `DirectionalLight()`
Constructs a DirectionalLight object.

## Properties

- `std::shared_ptr<Node> target`
  - Node that the light is directed towards.

## Functions

### `Direction()`
  - Returns the direction vector of the light.
### `GetType()`
  - Returns light type.
### `OnUpdate()`
  - Updates the light each frame.
### `SetDebugMode()`
  - Sets debug mode.
### `Create()`
  - Creates a shared pointer to an DirectionalLight object.
