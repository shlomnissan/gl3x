<!-- AUTO-GENERATED — do not edit. -->
# Renderer


Forward renderer for drawing a scene from a given camera.
The `Renderer` owns GPU state and draw logic for rendering a `Scene` with a specified `Camera`. It is typically constructed and driven by the `Application` runtime, but can also be used directly in manual setups.

Typical usage: 
```cpp
gleam::Renderer renderer({
  .framebuffer_width = window.FramebufferWidth(),
  .framebuffer_height = window.FramebufferHeight(),
  .clear_color = 0x444444
});

auto ok = renderer.Initialize();
if (!ok) {
  HandleError(ok.error());
}

// Per-frame:
renderer.Render(scene.get(), camera.get());
```

The renderer assumes a valid graphics context is current on the calling thread. When the window is resized, call `SetViewport()` to adjust the render area (or recreate with new parameters if you manage your own framebuffers).
## Constructors

### `Renderer()`
Constructs a renderer object with the given parameters.

## Functions

### `Initialize()`
  - Initializes GPU state and allocates required resources.
### `operator=()`
### `operator=()`
### `Render()`
  - Renders the given scene from the specified camera.
### `RenderedObjectsPerFrame()`
  - Returns the number of renderable objects drawn in the last frame.
### `SetClearColor()`
  - Sets the clear color for subsequent frames.
### `SetViewport()`
  - Sets the active viewport rectangle in pixels.
