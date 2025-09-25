<!-- AUTO-GENERATED — do not edit. -->
# Spherical


Spherical coordinates (radius, phi, theta).
Represents a point in 3D using spherical coordinates:`radius` is the distance from the origin.`phi` is the azimuth angle (yaw) in radians.`theta` is the polar angle (pitch) from the equator in radians.

`radius` is the distance from the origin.

`phi` is the azimuth angle (yaw) in radians.

`theta` is the polar angle (pitch) from the equator in radians.

This is useful for orbital camera rigs, sampling directions on a sphere, and converting to/from Cartesian coordinates.
## Properties

- `float phi`
   - Default value: `0.0f`
  - Azimuth angle (yaw) in radians.

- `float radius`
   - Default value: `1.0f`
  - Radial distance from the origin.

- `float theta`
   - Default value: `0.0f`
  - Polar angle (pitch) in radians.

## Functions

### `MakeSafe()`
  - Clamps theta (polar) away from the poles.
### `Spherical()`
  - Default constructor.
### `Spherical()`
  - Constructs a spherical coordinate from radius, phi, and theta.
### `ToVector3()`
  - Converts spherical to Cartesian coordinates.
