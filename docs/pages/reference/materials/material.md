<!-- AUTO-GENERATED — do not edit. -->
# Material


Abstract base class for material types.
Not intended for direct use.
## Properties

<div class="property-container">

<div class="property">
  <div class="definition"><span class="name">blending</span> <span class="type">Blending</span></div>
  <div class="description">
    Blending mode used for rendering this material.
    <div class="default">Default: <span class="value">{Blending::Normal}</span></div>
  </div>
</div>

<div class="property">
  <div class="definition">
  <span class="name">depth_test</span> <span class="type">bool</span></div>
  <div class="description">
    Enables depth testing.
    <div class="default">Default: <span class="value">{true}</span></div>
  </div>
</div>

<div class="property">
  <div class="definition">
  <span class="name">flat_shaded</span> <span class="type">bool</span></div>
  <div class="description">
    Enables flat shading.
    <div class="default">Default: <span class="value">{true}</span></div>
  </div>
</div>

<div class="property">
  <div class="definition">
  <span class="name">fog</span> <span class="type">bool</span></div>
  <div class="description">
    Enables scene fog for this material.
    <div class="default">Default: <span class="value">{true}</span></div>
  </div>
</div>

<div class="property">
  <div class="definition">
  <span class="name">opacity</span> <span class="type">float</span></div>
  <div class="description">
    Value in the range of <code>0.0f</code> - <code>1.0f</code> indicating how the material is.
    <div class="default">Default: <span class="value">{1.0f}</span></div>
  </div>
</div>

</div>

## Functions

### `GetType()`
  - Returns material type.
### `TypeToString()`
  - Converts material type enum value to string.
