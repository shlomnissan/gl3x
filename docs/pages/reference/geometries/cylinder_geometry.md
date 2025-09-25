<!-- AUTO-GENERATED — do not edit. -->
# CylinderGeometry


Generates a cylinder geometry assignable to any mesh.
`CylinderGeometry` creates a 3D cylinder composed of triangle primitives, with configurable top and bottom radii, height, and segment subdivisions. It can also be open-ended, excluding the caps.

```cpp
auto geometry = gleam::CylinderGeometry::Create({
    .radius_top = 0.8f,
    .radius_bottom = 1.0f,
    .height = 2.5f,
    .radial_segments = 32,
    .height_segments = 3,
    .open_ended = false
});

auto mesh = gleam::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
my_scene->Add(mesh);
```
## Constructors

### `CylinderGeometry()`
Constructs a CylinderGeometry object.

## Functions

### `Create()`
  - Creates a shared pointer to a CylinderGeometry object with default parameters.
### `Create()`
  - Creates a shared pointer to a CylinderGeometry object.
