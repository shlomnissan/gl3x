<!-- AUTO-GENERATED — do not edit. -->
# AmbientLight


Represents a light that gets emitted in all directions equally.
This light cannot be used to cast shadows as it does not have a direction.

```cpp
auto ambient_light = gleam::AmbientLight::Create({
  .color = 0xFFFFFF,
  .intensity = 0.3f
});
```
## Constructors

### `AmbientLight()`
Constructs an AmbientLight object.

## Functions

### `GetType()`
  - Returns light type.
### `Create()`
  - Creates a shared pointer to an AmbientLight object.
