<!-- AUTO-GENERATED — do not edit. -->
# Stats


Collects and visualizes runtime performance statistics.
The `Stats` class tracks frames per second, frame time, and the number of rendered objects per frame. It is used by the runtime when show_stats is set to true to provide an on-screen performance overlay during development and debugging.

Typical usage inside the main loop: 
```cpp
while (running) {
  stats.BeforeRender();
  renderer.Render(scene, camera);
  stats.AfterRender(renderer.RenderedObjectsPerFrame());
  stats.Draw();
}
```

This overlay requires ImGui support. If the engine is not compiled with `GLEAM_USE_IMGUI`, the `Draw()` method becomes a no-op.

This overlay requires ImGui support. If the engine is not compiled with `GLEAM_USE_IMGUI`, the `Draw()` method becomes a no-op.
