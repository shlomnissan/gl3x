# Application

The runtime entry point for defining and launching an app.

The `Application` class is the runtime: it sets up the window, rendering context, a main loop, and calls your hooks. Subclass it and override `Configure`, `CreateScene`, and `Update` to define behavior.

This is the preferred way to initialize a new app. If you need complete control, you can also assemble a program manually (window, renderer, loop, etc.), but that is outside the scope of this runtime API.

```cpp
class MyApp : public gleam::Application {
 public:
  auto Configure() -> Application::Parameters override {
    return {
      .title = "My App",
      .width = 1024,
      .height = 768,
      .clear_color = 0x444444,
      .vsync = true,
      .show_stats = true
    };
  }

  auto CreateScene() -> std::shared_ptr<gleam::Scene> override {
    auto scene = gleam::Scene::Create();
    // Add nodes to the scene...
    return scene;
  }

  // Optional: override CreateCamera() to provide your own camera.
  // Returning nullptr creates a default perspective camera.
  // auto CreateCamera() -> std::shared_ptr<gleam::Camera> override { ... }

  auto Update(float delta) -> bool override {
    // Per-frame logic. Return false to exit the main loop.
    return true;
  }
};

int main() {
  MyApp app;
  app.Start();
  return 0;
}
```

Calling `Start()` initializes the runtime, constructs the user scene (and camera, if provided), then runs the main loop while invoking `Update()` each frame.

## Constructor

#### `Application()`

Creates a new Application object.

Initializes internal state but does not start the application loop.
#### Parameters
- `camera` Shared pointer to the new [Camera]().

## Attributes

#### `Vector3 max {std::numeric_limits<float>::lowest()}`

Maximum corner of the box.

#### `Vector3 min {std::numeric_limits<float>::max()}`

Maximum corner of the box.

## Functions

#### `auto Update(float delta) -> bool`

Per-frame update callback.

This method must be implemented and is called every frame with the elapsed time since the last frame. Return false to exit the main loop.

**Returns** `true` to continue running, `false` to exit the main loop.

#### Parameters
- `delta` Time in seconds since the last frame.

#### `auto SetScene(std::shared_ptr<Scene> scene) -> void`

Sets the active scene.

#### Parameters
- `scene` Shared pointer to the new [Scene]().

## Source
[include/gleam/core/application.hpp]()