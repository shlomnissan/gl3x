<!-- AUTO-GENERATED — do not edit. -->
# Color


Represents an RGB color with floating-point components.
## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">b</span> <span class="type">float</span>
  ```cpp
  float b { 1.0f }
  ```
  </div>
  <div class="description">
    Blue channel [0.0, 1.0].
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">g</span> <span class="type">float</span>
  ```cpp
  float g { 1.0f }
  ```
  </div>
  <div class="description">
    Green channel [0.0, 1.0].
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">r</span> <span class="type">float</span>
  ```cpp
  float r { 1.0f }
  ```
  </div>
  <div class="description">
    Red channel [0.0, 1.0].
  </div>
</div>

## Functions

### `Color()`
  - Constructs a Color object.
### `Color()`
  - Constructs a Color object from individual RGB components.
### `Color()`
  - Constructs a Color object from a span of 3 float values.
### `Color()`
  - Constructs a Color object from a hexadecimal value.
### `operator*=()`
  - Multiplies the color by a scalar in-place.
### `operator=()`
  - Assigns a new color from a hexadecimal value.
### `operator[]()`
  - Accesses color components by index.
### `operator[]()`
  - Accesses color components by index (const).
### `Lerp()`
  - Linearly interpolates between two vectors.
