<!-- AUTO-GENERATED — do not edit. -->
# BoxGeometry


Generates a box geometry assignable to any mesh.
`BoxGeometry` creates a 3D box or rectangular box composed of triangles, based on configurable width, height, and depth. Optional segment parameters allow for subdividing each face, enabling smoother lighting or custom deformation effects.

```cpp
auto geometry = gleam::BoxGeometry::Create({
  .width = 2.0f,
  .height = 1.0f,
  .depth = 3.0f,
  .width_segments = 2,
  .height_segments = 2,
  .depth_segments = 2
});

auto mesh = gleam::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
my_scene->Add(mesh);
```
## Constructors

### `BoxGeometry()`
Constructs a BoxGeometry object.

## Functions

### `Create()`
  - Creates a shared pointer to a BoxGeometry object with default parameters.
### `Create()`
  - Creates a shared pointer to a BoxGeometry object.
