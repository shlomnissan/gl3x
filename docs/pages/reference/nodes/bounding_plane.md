<!-- AUTO-GENERATED — do not edit. -->
# BoundingPlane


Debug node that renders a bounding plane.
`BoundingPlane` is a visual helper used to display an infinite mathematical plane as a finite square region in the scene. This is particularly useful for visualizing clipping planes, frustum culling boundaries, or geometry intersections during debugging.

The plane is rendered as a flat square centered around the origin of the plane, oriented using the plane’s normal vector, and scaled based on the specified size.

```cpp
auto plane = gleam::Plane {Vector3::Forward(), 0.0f};
auto bounds = gleam::BoundingPlane::Create(plane, 2, 0xFF0000);
scene->Add(bounds);
```
## Constructors

### `BoundingPlane()`
Constructs a BoundingPlane object.

## Functions

### `Create()`
  - Creates a shared pointer to a BoundingPlane object.
