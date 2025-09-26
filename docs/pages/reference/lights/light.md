<!-- AUTO-GENERATED — do not edit. -->
# Light


Abstract base class for light types.
Not intended for direct use.
## Constructors

### `Light()`
Constructs a Light object.

## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">color</span> <span class="type">Color</span>
  ```cpp
  Color color { 0xffffff }
  ```
  </div>
  <div class="description">
    Light color, represented as RGB values.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">intensity</span> <span class="type">float</span>
  ```cpp
  float intensity { 1.0f }
  ```
  </div>
  <div class="description">
    Light intensity.
  </div>
</div>

## Functions

### `GetNodeType()`
  - Returns node type.
### `GetType()`
  - Returns light type.
### `SetDebugMode()`
  - Sets debug mode.
