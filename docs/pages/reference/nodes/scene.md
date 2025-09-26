<!-- AUTO-GENERATED — do not edit. -->
# Scene


Root node and entry point for a scene graph.
`Scene` is the top-level container for all nodes in a Gleam application. It acts as the root of the scene graph and is responsible for propagating update and input events throughout the hierarchy. Each application has one active scene at a time, which is managed by the `Application`.

A custom scene can be created by inheriting from this class and overriding behavior or adding initial nodes. The scene must be provided to the application during startup:

```cpp
class MyApp : public gleam::Application {
public:
  auto Configure() -> void override {
    params.title = "My App";
  }

  auto CreateScene() -> std::shared_ptr<gleam::Scene> override {
    auto scene = gleam::Scene::Create();
    // Add nodes to the scene
    return scene;
  }

  auto Update(float delta) -> bool override {
    // Called every frame
    return true;
  }
};
```

Only one scene can be attached to the application context at a time. Attaching a new scene using gleam::Application::SetScene replaces the current one.
## Constructors

### `Scene()`
Constructs an Scene instance.

## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">fog</span> <span class="type">std::unique_ptr&lt;Fog&gt;</span>
  ```cpp
  std::unique_ptr<Fog> fog 
  ```
  </div>
  <div class="description">
    Fog settings applied to the entire scene.
  </div>
</div>

## Functions

### `Advance()`
  - Advances the scene by one frame.
### `GetNodeType()`
  - Returns node type.
### `SetContext()`
  - Attaches a shared context to the scene.
### `Create()`
  - Creates a shared pointer to a Scene object.
