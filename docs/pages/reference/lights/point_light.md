<!-- AUTO-GENERATED — do not edit. -->
# PointLight


Represents a light that gets emitted from a single point in all directions.
A common use case for this is to replicate the light emitted from a bare lightbulb.

```cpp
auto point_light = gleam::PointLight::Create({
  .color = 0xFFFFFF,
  .intensity = 1.0f,
  .attenuation = {
    .base = 1.0f,
    .linear = 0.0f,
    .quadratic = 0.0f
  }
});
```
## Constructors

### `PointLight()`
Constructs a PointLight object.

## Properties

- `Attenuation attenuation`
  - Light attenuation properties.

## Functions

### `GetType()`
  - Returns light type.
### `OnUpdate()`
  - Updates the light each frame.
### `SetDebugMode()`
  - Sets debug mode.
### `Create()`
  - Creates a shared pointer to an PointLight object.
