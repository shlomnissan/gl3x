<!-- AUTO-GENERATED — do not edit. -->
# FrameTimer


Frame-oriented helper for computing clamped delta time.
`FrameTimer` builds on top of `Timer` to provide a simple, per-frame timestep (`dt`) suitable for driving simulations and animations. Each call to `Tick()` returns the elapsed time since the previous call, clamped by `max_delta` to guard against stalls (e.g., window drags, breakpoints).

Typical usage: 
```cpp
gleam::FrameTimer clock(true); // auto-start
while (running) {
  const float dt = clock.Tick(); // seconds (float), clamped
  scene.Advance(dt);
  renderer.Render(&scene, &camera);
}
```
## Constructors

### `FrameTimer()`
Constructs a FrameTimer object.

## Functions

### `Start()`
  - Starts the internal timer.
### `Tick()`
  - Returns the clamped time delta since the previous tick.
