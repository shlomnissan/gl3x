<!-- AUTO-GENERATED — do not edit. -->
# Plane


A plane defined by a normal vector and a distance from the origin.
The plane equation is defined as: dot(normal, point) + distance = 0. Used in collision tests, frustum culling, and geometry classification.
## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">distance</span> <span class="type">float</span>
  ```cpp
  float distance { 0.0f }
  ```
  </div>
  <div class="description">
    The signed distance from the origin to the plane along the normal.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">normal</span> <span class="type">Vector3</span>
  ```cpp
  Vector3 normal { Vector3::Up() }
  ```
  </div>
  <div class="description">
    The normal vector of the plane, pointing outward.
  </div>
</div>

## Functions

### `DistanceToPoint()`
  - Returns the signed distance from a point to the plane.
### `DistanceToSphere()`
  - Returns the signed distance from a sphere to the plane.
### `Normalize()`
  - Normalizes the plane equation.
### `Plane()`
  - Constructs a Plane with an upward normal and zero distance.
### `Plane()`
  - Constructs a Plane from a normal vector and distance.
