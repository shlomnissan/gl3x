<!-- AUTO-GENERATED — do not edit. -->
# LinearFog


Linearly interpolated fog effect, assignable to a scene.
This fog model applies a linear blend between no fog and full fog color based on fragment distance. It is intended to be assigned to a `Scene`'s `fog` field at runtime.

```cpp
my_scene->fog = gleam::LinearFog::Create(0x444444, 2.0f, 6.0f);
```
## Constructors

### `LinearFog()`
Constructs a LinearFog object.

## Properties

- `float far`
  - Distance at which fog reaches full opacity.

- `float near`
  - Distance at which fog starts.

## Functions

### `GetType()`
  - Returns fog type.
### `Create()`
  - Creates a shared pointer to a LinearFog object.
