<!-- AUTO-GENERATED — do not edit. -->
# Box3


Axis-aligned bounding box defined by minimum and maximum corners.
`Box3` represents a 3D volume bounded by two corners: `min` and `max`. It is used for spatial queries, frustum culling, and bounding volume computations. All operations assume the box is axis-aligned and defined in local space.
## Properties

- `Vector3 max`
   - Default value: `std::numeric_limits<float>::lowest()`
  - Maximum corner of the box.

- `Vector3 min`
   - Default value: `std::numeric_limits<float>::max()`
  - Minimum corner of the box.

## Functions

### `ApplyTransform()`
  - Transforms the box by the given matrix.
### `Box3()`
  - Constructs a Box3 object.
### `Box3()`
  - Constructs a Box3 object from minimum and maximum corners.
### `Center()`
  - Returns the center point of the box.
### `ExpandWithPoint()`
  - Expands the box to include the given point.
### `IsEmpty()`
  - Checks whether the box is empty (invalid).
### `Reset()`
  - Resets the box to an empty state.
### `Translate()`
  - Translates the box by a constant vector.
### `Union()`
  - Expands this box to fully contain another box.
