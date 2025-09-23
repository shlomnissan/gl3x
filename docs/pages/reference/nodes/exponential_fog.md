<!-- AUTO-GENERATED — do not edit. -->
# ExponentialFog


Exponential fog effect, assignable to a scene.
This fog model uses an exponential function based on view distance to simulate atmospheric fading. It is intended to be assigned to a `Scene`'s `fog` field at runtime.

```cpp
my_scene->fog = gleam::ExponentialFog::Create(0x888888, 0.15f);
```
