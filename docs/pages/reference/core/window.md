<!-- AUTO-GENERATED — do not edit. -->
# Window


Cross-platform application window.
The `Window` class creates the OS window and manages the framebuffer. It is typically managed by the `Application` runtime, but can also be constructed directly for manual initialization flows.

Typical usage: 
```cpp
gleam::Window window({
  .title = "My App",
  .width = 1280,
  .height = 720,
  .antialiasing = 4,
  .vsync = true
});

auto ok = window.Initialize();
if (!ok) {
  HandleError(ok.error());
}
```

Preferred usage is through the `Application` runtime, which wires the window, renderer, and scene automatically. Use direct initialization when you need full control over the main loop.
