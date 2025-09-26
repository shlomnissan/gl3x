<!-- AUTO-GENERATED — do not edit. -->
# Vector3


A 3D vector class for mathematical operations.
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

<div class="property">
  <div class="definition">

  ### <span class="name">z</span> <span class="type">float</span>
  ```cpp
  float z 
  ```
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
### `Vector3()`
  - Default constructor.
### `Vector3()`
  - Constructs a vector with all components set to the same value.
### `Vector3()`
  - Constructs a vector with specified x, y, and z components.
### `Forward()`
  - Returns the unit vector pointing forward (0, 0, 1).
### `Right()`
  - Returns the unit vector pointing to the right (1, 0, 0).
### `Up()`
  - Returns the unit vector pointing upward (0, 1, 0).
### `Zero()`
  - Returns a zero vector (0, 0, 0).
### `Cross()`
  - Computes the cross product between two vectors.
### `Dot()`
  - Computes the dot product between two vectors.
### `Lerp()`
  - Linearly interpolates between two vectors.
### `Normalize()`
  - Returns a normalized copy of the given vector.
