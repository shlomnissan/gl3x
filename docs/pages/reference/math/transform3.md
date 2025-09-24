<!-- AUTO-GENERATED — do not edit. -->
# Transform3


A 3D transformation class supporting translation, scaling, and rotation.
Internally manages position, scale, and rotation in Euler angles. Lazily computes the final transformation matrix when accessed.
## Properties

- `Vector3 position`
   - Default value: `0.0f`
  - World-space translation.

- `Euler rotation`
  - Euler rotation (pitch, yaw, roll).

- `Vector3 scale`
   - Default value: `1.0f`
  - Local scale.

- `bool touched`
   - Default value: `true`
  - Indicates whether the transformation matrix needs to be recomputed.
