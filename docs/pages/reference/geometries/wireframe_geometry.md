<!-- AUTO-GENERATED — do not edit. -->
# WireframeGeometry


Converts triangle-based geometry into wireframe-renderable geometry.
`WireframeGeometry` takes an existing indexed geometry and generates a new geometry that can be rendered using `GeometryPrimitiveType::Lines`. It preserves the original vertex data and replaces the index buffer with one that represents the edges of the original triangle mesh.

This is commonly used for debugging purposes, such as visualizing mesh topology, bounding volumes, or silhouette edges.

```cpp
auto original = gleam::BoxGeometry::Create();
auto wireframe = std::make_shared<gleam::WireframeGeometry>(original.get());
mesh->geometry = wireframe;
```

The source geometry must be triangle-based and contain valid index data.
