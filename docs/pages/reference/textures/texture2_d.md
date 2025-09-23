<!-- AUTO-GENERATED — do not edit. -->
# Texture2D


Represents a 2D texture that can be attached to materials.
While you can instantiate a Texture2D object directly, it is recommended to use the texture loader object to create texture instances:

```cpp
auto MyNode::OnAttached(SharedContextPointer context) -> void override {
  context->texture_loader->LoadAsync(
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
