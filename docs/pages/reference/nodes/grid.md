<!-- AUTO-GENERATED — do not edit. -->
# Grid


Visual primitive representing a finite reference grid on the XZ plane.
`Grid` is a scene node used to display a uniform grid, typically for orientation and spatial reference in 3D scenes. It is useful during development to visualize world units and object placement.

The grid is centered at the origin and lies flat on the XZ plane. Grid lines are evenly spaced based on the provided size and division count.

```cpp
auto grid = gleam::Grid::Create({
    .size = 4.0f,
    .divisions = 16,
    .color = 0x333333
});
scene->Add(grid);
```
## Constructors

### `Grid()`
Constructs a Grid object.

## Functions

### `Create()`
  - Creates a shared pointer to a Grid object.
