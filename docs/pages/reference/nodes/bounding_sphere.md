<!-- AUTO-GENERATED — do not edit. -->
# BoundingSphere


Debug node that renders a bounding sphere.
`BoundingSphere` is a visual helper used to display a wireframe sphere representing the spatial bounds of an object or volume. It is primarily used for debugging, spatial queries, or visibility testing.

The sphere is defined in local space using a `Sphere` object and rendered as a wireframe in the specified color.

```cpp
auto geometry = gleam::BoxGeometry::Create();
auto bounds = gleam::BoundingSphere::Create(
  geometry->BoundingSphere(),
  0xFF0000
);
scene->Add(bounds);
```
