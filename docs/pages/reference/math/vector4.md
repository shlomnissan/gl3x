<!-- AUTO-GENERATED — do not edit. -->
# Vector4


A 4D vector class for mathematical operations.
## Properties

<div class="property">
  <div class="definition">
    <span class="name">w</span> <span class="type">float</span>
  </div>
  <div class="description">
    W component of the vector.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">x</span> <span class="type">float</span>
  </div>
  <div class="description">
    X component of the vector.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">y</span> <span class="type">float</span>
  </div>
  <div class="description">
    Y component of the vector.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">z</span> <span class="type">float</span>
  </div>
  <div class="description">
    Z component of the vector.
  </div>
</div>

## Functions

### `Length()`
  - Computes the approximate magnitude of the vector.
### `LengthSquared()`
  - Computes the squared length (magnitude) of the vector.
### `Max()`
  - Component-wise in-place maximum.
### `Min()`
  - Component-wise in-place minimum.
### `Normalize()`
  - Normalizes the vector in-place.
### `operator*=()`
  - Scales each component by another vector.
### `operator*=()`
  - Scales the vector by a scalar.
### `operator+=()`
  - Adds another vector to this one.
### `operator-=()`
  - Subtracts another vector from this one.
### `operator[]()`
  - Accesses vector components by index.
### `operator[]()`
  - Accesses vector components by index (const).
### `Vector4()`
  - Default constructor.
### `Vector4()`
  - Constructs a vector with all components set to the same value.
### `Vector4()`
  - Constructs a vector with specified x, y, z, and w components.
### `Zero()`
  - Returns a zero vector (0, 0, 0, 0).
### `Dot()`
  - Computes the dot product between two vectors.
### `Lerp()`
  - Linearly interpolates between two vectors.
### `Normalize()`
  - Returns a normalized copy of the given vector.
