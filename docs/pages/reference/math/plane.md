<!-- AUTO-GENERATED — do not edit. -->
# Plane


A plane defined by a normal vector and a distance from the origin.
The plane equation is defined as: dot(normal, point) + distance = 0. Used in collision tests, frustum culling, and geometry classification.
## Properties

- `float distance`
   - Default value: `0.0f`
  - The signed distance from the origin to the plane along the normal.

- `Vector3 normal`
   - Default value: `Vector3::Up()`
  - The normal vector of the plane, pointing outward.
