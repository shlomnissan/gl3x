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
## Constructors

### `Window()`
Constructs a window object with the given parameters.

## Functions

### `AspectRatio()`
  - Returns the logical aspect ratio (width / height).
### `BeginUIFrame()`
  - Marks the beginning of a new UI frame.
### `EndUIFrame()`
  - Marks the end of the current UI frame.
### `FramebufferHeight()`
  - Returns the current framebuffer height in pixels.
### `FramebufferWidth()`
  - Returns the current framebuffer width in pixels.
### `Height()`
  - Returns the current logical window height in pixels.
### `Initialize()`
  - Initializes the underlying OS window and graphics context.
### `OnResize()`
  - Registers a callback to be invoked when the window is resized.
### `operator=()`
### `operator=()`
### `PollEvents()`
  - Processes pending window and input events.
### `RequestClose()`
  - Requests that the window be closed.
### `SetTitle()`
  - Updates the window title string.
### `ShouldClose()`
  - Returns whether the window has been flagged for closing.
### `SwapBuffers()`
  - Swaps the front and back buffers.
### `Width()`
  - Returns the current logical window width in pixels.
