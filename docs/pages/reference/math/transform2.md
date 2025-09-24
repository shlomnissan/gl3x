<!-- AUTO-GENERATED — do not edit. -->
# Transform2


A 2D transformation class supporting translation, scaling, and rotation.
Internally manages position, scale, rotation, and center of transformation. Lazily computes the final transformation matrix when accessed.
## Properties

- `Vector2 center`
   - Default value: `0.0f, 0.0f`
  - Pivot for rotation and scaling.

- `Vector2 position`
   - Default value: `0.0f, 0.0f`
  - World-space translation.

- `float rotation`
   - Default value: `0.0f`
  - Rotation angle in radians.

- `Vector2 scale`
   - Default value: `1.0f, 1.0f`
  - Local scale.

- `bool touched`
   - Default value: `true`
  - Indicates whether the transformation matrix needs to be recomputed.
