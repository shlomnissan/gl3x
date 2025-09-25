<!-- AUTO-GENERATED — do not edit. -->
# Matrix3


A 3x3 matrix class for mathematical operations.
Stores the matrix in column-major order using three Vector3 columns. Commonly used for representing linear transformations.
## Functions

### `Matrix3()`
  - Constructs a Matrix3 object.
### `Matrix3()`
  - Constructs a Matrix3 object from a Matrix4.
### `Matrix3()`
  - Constructs a Matrix3 object from three column vectors.
### `Matrix3()`
  - Constructs a Matrix3 object from individual components (row-major).
### `Matrix3()`
  - Constructs a diagonal Matrix3 with the given scalar value.
### `operator()()`
  - Access matrix element by (row, column).
### `operator()()`
  - Access matrix element by (row, column) (const).
### `operator[]()`
  - Access matrix column vector by index.
### `operator[]()`
  - Access matrix column vector by index (const).
### `Identity()`
  - Returns the identity matrix.
### `Determinant()`
  - Computes the determinant of a Matrix3 object.
### `Inverse()`
  - Computes the inverse of a Matrix3 object.
### `Transpose()`
  - Computes the transpose of a Matrix3 object.
