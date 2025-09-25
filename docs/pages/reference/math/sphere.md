<!-- AUTO-GENERATED — do not edit. -->
# Sphere


A bounding sphere defined by a center point and radius.
Useful for fast intersection tests, frustum culling, and spatial bounds.
## Properties

- `Vector3 center`
   - Default value: `Vector3::Zero()`
  - Center of the sphere in 3D space.

- `float radius`
   - Default value: `-1.0f`
  - Radius of the sphere. A negative value indicates an empty sphere.

## Functions

### `ApplyTransform()`
  - Transforms the sphere by the given matrix.
### `ExpandWithPoint()`
  - Expands the sphere to include a given point.
### `IsEmpty()`
  - Checks if the sphere is empty.
### `Radius()`
  - Returns the current radius of the sphere.
### `Reset()`
  - Resets the sphere to an empty state.
### `Sphere()`
  - Constructs a Sphere with a negative (empty) radius.
### `Sphere()`
  - Constructs a Sphere from a center and a radius.
### `Translate()`
  - Translates the sphere by a constant vector.
### `Union()`
  - Expands this sphere to fully contain another sphere.
