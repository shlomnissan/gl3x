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

The renderer assumes a valid graphics context is current on the calling thread. When the window is resized, call `SetViewport()` to adjust the render area (or recreate with new parameters if you manage your own framebuffers).
