<!-- AUTO-GENERATED — do not edit. -->
# OrbitControls


Interactive camera controller for orbiting around a target point.
`OrbitControls` enables intuitive camera manipulation using spherical coordinates, allowing users to orbit, zoom, and pan around a fixed target. It is typically attached to a scene node and linked to a `Camera` instance, responding to mouse input and updating camera transforms each frame.

This controller is useful for editor views, previews, and navigation interfaces.

```cpp
auto MyScene::OnAttached(SharedContextPointer context) -> void override {
  Add(gleam::OrbitControls::Create(
    context->camera, {
      .radius = 5.0f,
      .pitch = math::DegToRad(25.0f),
      .yaw = math::DegToRad(45.0f)
    }
  ));
}
```
## Properties

- `float orbit_speed`
   - Default value: `3.5f`
  - Rate at which the camera orbits around the target point.

- `float pan_speed`
   - Default value: `0.5f`
  - Rate at which the camera pans around the target point.

- `float zoom_speed`
   - Default value: `50.0f`
  - Rate at which the camera zooms in and out.
