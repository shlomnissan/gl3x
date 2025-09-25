<!-- AUTO-GENERATED — do not edit. -->
# MeshLoader


Loads mesh data from engine-optimized `.msh` files.
This class implements the abstract Loader interface to load Mesh objects from the file system, specifically targeting the engine's custom `.msh` format, which encapsulates optimized mesh data along with associated materials. It supports both synchronous and asynchronous loading through the base Loader API.

This class returns an Node object, which serves as a group container encapsulating one or more static Mesh objects.

You can convert common 3D model formats (e.g., OBJ, FBX) into `.msh` files using the `asset_builder` - a command-line tool located in the tools directory.

Explicit instantiation of this class is discouraged due to potential lifetime issues in the current architecture, particularly when used with asynchronous loading. Instead, access it through the Node::OnAttached hook, which provides a reference to the context that owns an instance of this class.

```cpp
auto MyNode::OnAttached(SharedContextPointer context) -> void override {
  context->mesh_loader->LoadAsync(
    "assets/my_model.msh",
    [this](auto result) {
      if (result) {
        this->Add(result.value());
      } else {
        std::println(stderr, "{}", result.error());
      }
    }
  );
}
```

Loaders use `std::expect` for error values. Always check that loading operations return a valid result, and handle the error otherwise.
## Functions

### `Create()`
  - Creates a shared pointer to a MeshLoader object.
