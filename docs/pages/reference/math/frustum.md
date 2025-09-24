<!-- AUTO-GENERATED — do not edit. -->
# Frustum


Represents a view frustum defined by six clipping planes.
A `Frustum` is used for view frustum culling by the renderer, enabling efficient rejection of geometry outside the visible camera volume. It is constructed from a view-projection matrix and defines six planes: left, right, top, bottom, near, and far.

This class supports containment and intersection tests with points, axis-aligned bounding boxes (AABB), and bounding spheres. All tests assume the frustum planes face inward.
## Properties

- `std::array<Plane, 6 > planes`
  - The six clipping planes of the frustum: left, right, top, bottom, near, far.
