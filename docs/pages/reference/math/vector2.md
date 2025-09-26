<!-- AUTO-GENERATED — do not edit. -->
# Vector2


A 2D vector class for mathematical operations.
## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">x</span> <span class="type">float</span>
  ```cpp
  float x 
  ```
  </div>
  <div class="description">
    X component of the vector.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">y</span> <span class="type">float</span>
  ```cpp
  float y 
  ```
  </div>
  <div class="description">
    Y component of the vector.
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
### `Vector2()`
  - Default constructor.
### `Vector2()`
  - Constructs a vector with both components set to the same value.
### `Vector2()`
  - Constructs a vector with specified x and y components.
### `Right()`
  - Returns the unit vector pointing to the right (1, 0).
### `Up()`
  - Returns the unit vector pointing upward (0, 1).
### `Zero()`
  - Returns a zero vector (0, 0).
### `Dot()`
  - Computes the dot product between two vectors.
### `Lerp()`
  - Linearly interpolates between two vectors.
### `Normalize()`
  - Returns a normalized copy of the given vector.
