/*

This snippet includes common shader utility functions.

@func void isPerspectiveMatrix(in mat4 m)
- @desc Returns true if projection matrix applies perspective projection.
- @param mat4 m - Projection matrix
- @return bool

*/

bool isPerspectiveMatrix(in mat4 m) {
    return m[2][3] == -1.0;
}