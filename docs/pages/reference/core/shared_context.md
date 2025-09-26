<!-- AUTO-GENERATED — do not edit. -->
# SharedContext


Provides access to shared parameters and services.
The `SharedContext` class encapsulates common runtime parameters and services that are shared across the scene graph. This context is created internally within the runtime and made available to nodes once they are added to the active scene.

Access to the shared context is provided through the `Node::OnAttached(SharedContextPointer context)` callback, which is invoked when the node becomes part of an active scene hierarchy. Override this method in your node class to perform initialization that depends on the context, such as loading resources, accessing the active camera, etc.

```cpp
class MyNode : public gleam::Node {
public:
  void OnAttached(SharedContextPointer context) override {
    context->texture_loader->LoadAsync(
      "assets/checker.tex",
      [this](auto result) {
        if (result) {
          texture_ = result.value();
        } else {
          std::println(stderr, "{}", result.error());
        }
      }
    );
  }
};
```
## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">aspect_ratio</span> <span class="type">float</span>
  ```cpp
  float aspect_ratio 
  ```
  </div>
  <div class="description">
    Aspect ratio of the render surface.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">camera</span> <span class="type">Camera*</span>
  ```cpp
  Camera* camera 
  ```
  </div>
  <div class="description">
    Current active camera.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">framebuffer_height</span> <span class="type">int</span>
  ```cpp
  int framebuffer_height 
  ```
  </div>
  <div class="description">
    Frambuffer height in physical pixels.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">framebuffer_width</span> <span class="type">int</span>
  ```cpp
  int framebuffer_width 
  ```
  </div>
  <div class="description">
    Framebuffer width in physical pixels.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">mesh_loader</span> <span class="type">std::shared_ptr&lt;MeshLoader&gt;</span>
  ```cpp
  std::shared_ptr<MeshLoader> mesh_loader { MeshLoader::Create() }
  ```
  </div>
  <div class="description">
    Mesh loader.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">texture_loader</span> <span class="type">std::shared_ptr&lt;TextureLoader&gt;</span>
  ```cpp
  std::shared_ptr<TextureLoader> texture_loader { TextureLoader::Create() }
  ```
  </div>
  <div class="description">
    Texture loader.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">window_height</span> <span class="type">int</span>
  ```cpp
  int window_height 
  ```
  </div>
  <div class="description">
    Window height in logical units.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">window_width</span> <span class="type">int</span>
  ```cpp
  int window_width 
  ```
  </div>
  <div class="description">
    Window width in logical units.
  </div>
</div>
