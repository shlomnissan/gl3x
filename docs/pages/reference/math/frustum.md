<!-- AUTO-GENERATED — do not edit. -->
# Frustum


Represents a view frustum defined by six clipping planes.
A `Frustum` is used for view frustum culling by the renderer, enabling efficient rejection of geometry outside the visible camera volume. It is constructed from a view-projection matrix and defines six planes: left, right, top, bottom, near, and far.

This class supports containment and intersection tests with points, axis-aligned bounding boxes (AABB), and bounding spheres. All tests assume the frustum planes face inward.
## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">planes</span> <span class="type">std::array&lt;Plane, 6 &gt;</span>
  ```cpp
  std::array<Plane, 6 > planes 
  ```
  </div>
  <div class="description">
    The six clipping planes of the frustum: left, right, top, bottom, near, far.
  </div>
</div>

## Functions

### `ContainsPoint()`
  - Checks whether a point is inside the frustum.
### `Frustum()`
  - Constructs a Frustum object.
### `Frustum()`
  - Constructs a Frustum object from a view-projection matrix.
### `IntersectsWithBox3()`
  - Checks whether an axis-aligned bounding box intersects the frustum.
### `IntersectsWithSphere()`
  - Checks whether a sphere intersects the frustum.
### `SetWithViewProjection()`
  - Updates the frustum using a new view-projection matrix.
