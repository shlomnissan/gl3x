<!-- AUTO-GENERATED — do not edit. -->
# Material


Abstract base class for material types.
Not intended for direct use.
## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">blending</span> <span class="type">Blending</span>
  ```cpp
  Blending blending { Blending::Normal }
  ```
  </div>
  <div class="description">
    Blending mode used for rendering this material.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">depth_test</span> <span class="type">bool</span>
  ```cpp
  bool depth_test { true }
  ```
  </div>
  <div class="description">
    Enables depth testing.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">flat_shaded</span> <span class="type">bool</span>
  ```cpp
  bool flat_shaded { false }
  ```
  </div>
  <div class="description">
    Enables flat shading.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">fog</span> <span class="type">bool</span>
  ```cpp
  bool fog { true }
  ```
  </div>
  <div class="description">
    Enables scene fog for this material.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">opacity</span> <span class="type">float</span>
  ```cpp
  float opacity { 1.0f }
  ```
  </div>
  <div class="description">
    Value in the range of <code>0.0</code> - <code>1.0</code> indicating how transparent the material is.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">polygon_offset_factor</span> <span class="type">float</span>
  ```cpp
  float polygon_offset_factor { 0.0f }
  ```
  </div>
  <div class="description">
    Sets the polygon offset factor.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">polygon_offset_units</span> <span class="type">float</span>
  ```cpp
  float polygon_offset_units { 0.0f }
  ```
  </div>
  <div class="description">
    Sets the polygon offset units.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">transparent</span> <span class="type">bool</span>
  ```cpp
  bool transparent { false }
  ```
  </div>
  <div class="description">
    Enables transparency.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">two_sided</span> <span class="type">bool</span>
  ```cpp
  bool two_sided { false }
  ```
  </div>
  <div class="description">
    Enables rendering both front and back faces of polygons.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">visible</span> <span class="type">bool</span>
  ```cpp
  bool visible { true }
  ```
  </div>
  <div class="description">
    Enables visibility.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">wireframe</span> <span class="type">bool</span>
  ```cpp
  bool wireframe { false }
  ```
  </div>
  <div class="description">
    Enables wireframe rendering.
  </div>
</div>

## Functions

### `GetType()`
  - Returns material type.
### `TypeToString()`
  - Converts material type enum value to string.
