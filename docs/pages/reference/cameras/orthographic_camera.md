<!-- AUTO-GENERATED — do not edit. -->
# OrthographicCamera


Represents a camera that uses orthographic projection.
In this projection mode, an object's size in the rendered image stays constant regardless of its distance from the camera. This can be useful for rendering 2D scenes and UI elements, amongst other things.

Although multiple cameras can be added to the scene graph and inherit transformations from their parent objects, only one camera can be active at a time. The active camera is managed by the application’s runtime object: 
```cpp
class MyApp : public gleam::Application {
public:
  auto Configure() -> void override {}

  auto Setup() -> void override {
    SetCamera(gleam::OrthographicCamera::Create({
      .left = 0.0f,
      .right = 1024.0f,
      .top = 0.0f,
      .bottom = 768.0f,
      .near = 0.1f,
      .far = 100.0f
    }));
  }

  auto Update(float delta) -> bool override {
    return true;
  }
}
```
