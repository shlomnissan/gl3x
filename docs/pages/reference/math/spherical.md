<!-- AUTO-GENERATED — do not edit. -->
# Spherical


Spherical coordinates (radius, phi, theta).
Represents a point in 3D using spherical coordinates:`radius` is the distance from the origin.`phi` is the azimuth angle (yaw) in radians.`theta` is the polar angle (pitch) from the equator in radians.

`radius` is the distance from the origin.

`phi` is the azimuth angle (yaw) in radians.

`theta` is the polar angle (pitch) from the equator in radians.

This is useful for orbital camera rigs, sampling directions on a sphere, and converting to/from Cartesian coordinates.
## Properties

<div class="property">
  <div class="definition">
    <span class="name">phi</span> <span class="type">float</span>
  </div>
  <div class="description">
    Azimuth angle (yaw) in radians.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">radius</span> <span class="type">float</span>
  </div>
  <div class="description">
    Radial distance from the origin.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">theta</span> <span class="type">float</span>
  </div>
  <div class="description">
    Polar angle (pitch) in radians.
  </div>
</div>

## Functions

### `MakeSafe()`
  - Clamps theta (polar) away from the poles.
### `Spherical()`
  - Default constructor.
### `Spherical()`
  - Constructs a spherical coordinate from radius, phi, and theta.
### `ToVector3()`
  - Converts spherical to Cartesian coordinates.
