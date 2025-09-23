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
