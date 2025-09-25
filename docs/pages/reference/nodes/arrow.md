<!-- AUTO-GENERATED — do not edit. -->
# Arrow


Visual debug primitive representing a 3D arrow.
`Arrow` is a scene node that renders a directional arrow from a given origin, primarily used for debugging, orientation helpers, or coordinate indicators. It is constructed from a shaft and cone head, scaled based on the provided length.

The arrow can be positioned using `SetOrigin()` and oriented using `SetDirection()`.

```cpp
auto arrow = gleam::Arrow::Create({
  .direction = {1.0f, 0.0f, 0.0f},
  .origin = Vector3::Zero(),
  .color = 0xFF0000,
  .length = 1.0f
});
scene->Add(arrow);
```
## Constructors

### `Arrow()`
Constructs an Arrow object.

## Functions

### `SetDirection()`
  - Sets the direction of the arrow.
### `SetOrigin()`
  - Sets the origin of the arrow.
### `Create()`
  - Creates a shared pointer to an Arrow object.
