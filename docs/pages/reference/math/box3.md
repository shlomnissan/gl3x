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
