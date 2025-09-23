<!-- AUTO-GENERATED — do not edit. -->
# PerspectiveCamera


Represents a camera that uses perspective projection.
This projection mode is designed to mimic the way the human eye sees. It is the most common projection mode used for rendering a 3D scene.

Although multiple cameras can be added to the scene graph and inherit transformations from their parent objects, only one camera can be active at a time. The active camera is managed by the application’s runtime object: 
```cpp
class MyApp : public gleam::Application {
public:
  auto Configure() -> void override {}

  auto Setup() -> void override {
    SetCamera(gleam::PerspectiveCamera::Create({
      .fov = gleam::math::DegToRad(60.0f),
      .aspect = Context()->Parameters().ratio,
      .near = 0.1f,
      .far = 1000.0f
    }));
  }

  auto Update(float delta) -> bool override {
    return true;
  }
}
```
