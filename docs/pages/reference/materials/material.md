<!-- AUTO-GENERATED — do not edit. -->
# Material


Abstract base class for material types.
Not intended for direct use.
## Properties

- `Blending blending`
   - Default value: `Blending::Normal`
  - Blending mode used for rendering this material.

- `bool depth_test`
   - Default value: `true`
  - Enables depth testing.

- `bool flat_shaded`
   - Default value: `false`
  - Enables flat shading.

- `bool fog`
   - Default value: `true`
  - Enables scene fog for this material.

- `float opacity`
   - Default value: `1.0f`
  - Value in the range of `0.0` - `1.0` indicating how transparent the material is.

- `float polygon_offset_factor`
   - Default value: `0.0f`
  - Sets the polygon offset factor.

- `float polygon_offset_units`
   - Default value: `0.0f`
  - Sets the polygon offset units.

- `bool transparent`
   - Default value: `false`
  - Enables transparency.

- `bool two_sided`
   - Default value: `false`
  - Enables rendering both front and back faces of polygons.

- `bool visible`
   - Default value: `true`
  - Enables visibility.

- `bool wireframe`
   - Default value: `false`
  - Enables wireframe rendering.

## Functions

### `GetType()`
  - Returns material type.
### `TypeToString()`
  - Converts material type enum value to string.
