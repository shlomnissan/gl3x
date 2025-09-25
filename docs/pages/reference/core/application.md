<!-- AUTO-GENERATED — do not edit. -->
# Application


The runtime entry point for defining and launching an app.
The `Application` class is the runtime: it sets up the window, rendering context, a main loop, and calls your hooks. Subclass it and override `Configure`, `CreateScene`, and `Update` to define behavior.

This is the preferred way to initialize a new app. If you need complete control, you can also assemble a program manually (window, renderer, loop, etc.), but that is outside the scope of this runtime API.

Typical usage:

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
## Constructors

### `Application()`
Constructs an Application instance.

## Functions

### `Configure()`
  - Provides configuration parameters for the application.
### `CreateCamera()`
  - Creates the main camera.
### `CreateScene()`
  - Creates the root scene graph.
### `GetCamera()`
  - Returns the current camera pointer.
### `GetContext()`
  - Returns the active shared context.
### `GetScene()`
  - Returns the current scene pointer.
### `operator=()`
### `operator=()`
### `SetCamera()`
  - Sets the active camera.
### `SetScene()`
  - Sets the active scene.
### `Start()`
  - Starts the application loop.
### `Update()`
  - Per-frame update callback.
