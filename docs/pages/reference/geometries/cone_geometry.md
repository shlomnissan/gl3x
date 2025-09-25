<!-- AUTO-GENERATED — do not edit. -->
# ConeGeometry


Generates a cone geometry assignable to any mesh.
`ConeGeometry` creates a 3D cone shape with configurable radius, height, and segment subdivisions. It is rendered using triangle primitives and can optionally exclude the bottom cap (open-ended).

```cpp
auto geometry = gleam::ConeGeometry::Create({
  .radius = 0.5f,
  .height = 2.0f,
  .radial_segments = 32,
  .height_segments = 4,
  .open_ended = false
});

auto mesh = gleam::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
my_scene->Add(mesh);
```
## Constructors

### `ConeGeometry()`
Constructs a ConeGeometry object.

## Functions

### `Create()`
  - Creates a shared pointer to a ConeGeometry object with default parameters.
### `Create()`
  - Creates a shared pointer to a ConeGeometry object.
