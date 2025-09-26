<!-- AUTO-GENERATED — do not edit. -->
# ExponentialFog


Exponential fog effect, assignable to a scene.
This fog model uses an exponential function based on view distance to simulate atmospheric fading. It is intended to be assigned to a `Scene`'s `fog` field at runtime.

```cpp
my_scene->fog = gleam::ExponentialFog::Create(0x888888, 0.15f);
```
## Constructors

### `ExponentialFog()`
Constructs an ExponentialFog object.

## Properties

<div class="property">
  <div class="definition">
    <span class="name">density</span> <span class="type">float</span>
  </div>
  <div class="description">
    Density factor controlling fog steepness.
  </div>
</div>

## Functions

### `GetType()`
  - Returns fog type.
### `Create()`
  - Creates a shared pointer to an ExponentialFog object.
