<!-- AUTO-GENERATED — do not edit. -->
# SpotLight


Represents a light that emits in a specific direction with a cone-shaped area of influence.
The light intensity diminishes both with distance and with the angle from the central axis of the cone. This type of light is commonly used to simulate focused sources such as flashlights or stage spotlights, where illumination is limited to a defined region and falls off outside of it.

```cpp
auto spot_light = gleam::SpotLight::Create({
  .color = 0xFFFFFF,
  .intensity = 1.0f,
  .angle = gleam::math::DegToRad(10.0f),
  .penumbra = 0.3f,
  .target = nullptr,
  .attenuation = {
    .base = 1.0f,
    .linear = 0.0f,
    .quadratic = 0.0f
  }
});
```

When the target parameter is set to `nullptr` the light points to (0, 0, 0).
## Constructors

### `SpotLight()`
Constructs a SpotLight object.

## Properties

- `float angle`
  - Angle, in radians, of the spotlight's cone.

- `Attenuation attenuation`
  - Light attenuation properties.

- `float penumbra`
  - Penumbra value controlling the softness of the spotlight's edge.

- `std::shared_ptr<Node> target`
   - Default value: `nullptr`
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
  - Creates a shared pointer to a SpotLight object.
