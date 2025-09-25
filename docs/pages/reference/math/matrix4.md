<!-- AUTO-GENERATED — do not edit. -->
# Matrix4


A 4x4 matrix class for mathematical operations.
Stores the matrix in column-major order using four Vector4 columns. Commonly used for 3D transformations including translation, rotation, scaling, and projection.
## Functions

### `Matrix4()`
  - Constructs a Matrix4 object.
### `Matrix4()`
  - Constructs a Matrix4 object from four column vectors.
### `Matrix4()`
  - Constructs a Matrix4 object from individual components (row-major).
### `Matrix4()`
  - Constructs a diagonal Matrix4 with the given scalar value.
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
  - Computes the determinant of a Matrix4 object.
### `Inverse()`
  - Computes the inverse of a Matrix4 object.
### `Transpose()`
  - Computes the transpose of a Matrix4 object.
