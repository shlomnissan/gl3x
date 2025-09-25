<!-- AUTO-GENERATED — do not edit. -->
# BoundingBox


Debug node that renders an axis-aligned bounding box.
`BoundingBox` is a visual helper used to display a wireframe box representing the spatial bounds of an object or region. It is commonly used for debugging, collision visualization, or spatial partitioning diagnostics.

The box is defined in local space using a `Box3` volume and rendered as lines in the specified color.

```cpp
auto geometry = gleam::SphereGeometry::Create();
auto bounds = gleam::BoundingBox::Create(
  geometry->BoundingBox(),
  0xFFFFFF
);
scene->Add(bounds);
```
## Constructors

### `BoundingBox()`
Constructs a BoundingBox object.

## Functions

### `Create()`
  - Creates a shared pointer to a BoundingBox object.
