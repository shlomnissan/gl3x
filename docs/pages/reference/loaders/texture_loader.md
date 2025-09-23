<!-- AUTO-GENERATED — do not edit. -->
# TextureLoader


Loads 2D textures from engine-optimized `.tex` files.
This class implements the abstract Loader interface to load Texture2D resources from the file system, specifically targeting the engine's custom `.tex` format. It supports both synchronous and asynchronous loading through the base Loader API.

You can convert standard image formats (e.g., PNG, JPG) into `.tex` files using the `asset_builder` - a command-line tool located in the tools directory.

Explicit instantiation of this class is discouraged due to potential lifetime issues in the current architecture, particularly when used with asynchronous loading. Instead, access it through the Node::OnAttached hook, which provides a reference to the context that owns an instance of this class.

```cpp
auto MyNode::OnAttached(SharedContextPointer context) -> void override {
  context->loaders.Texture->LoadAsync(
    "assets/my_texture.tex",
    [this](auto result) {
      if (result) {
        texture_ = result.value();
      } else {
        std::println(stderr, "{}", result.error());
      }
     }
  );
}
```

Loaders use `std::expect` for error values. Always check that loading operations return a valid result, and handle the error otherwise.
