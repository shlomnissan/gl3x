<!-- AUTO-GENERATED — do not edit. -->
# Material


Abstract base class for material types.
Not intended for direct use.
## Properties

<div class="property">
  <div class="definition"><span class="name">blending</span> <span class="type">Blending</span></div>
  <div class="description">
    Blending mode used for rendering this material.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">depth_test</span> <span class="type">bool</span>
  </div>
  <div class="description">
    Enables depth testing.
  </div>
</div>

## Functions

<div class="function">
  <div class="definition">
    <span class="name">GetType</span>(<span class="param"><span class="param-type">Vector3</span> <span class="param-name">target</span></span>, <span class="param"><span class="param-type">Vector3</span> <span class="param-name">position</span></span>) <span class="return">-> Vector3</span>
  </div>
  <div class="description">
    Returns a Vector3 representing the world space direction in which the camera is looking. (Note: A camera looks down its local, negative z-axis).
  </div>
  <ul class="params">
    <li><span class="param-name">target</span> - Node to orient the camera towards</li>
    <li><span class="param-name">position</span> - Position of the camera node</li>
  </ul>
</div>

<div class="function">
  <div class="definition">
    <span class="name">TypeToString</span>(<span class="param"><span class="param-type">Vector3</span> <span class="param-name">target</span></span>, <span class="param"><span class="param-type">Vector3</span> <span class="param-name">position</span></span>) <span class="return">-> void</span>
  </div>
  <div class="description">
    Returns a Vector3 representing the world space direction in which the camera is looking. (Note: A camera looks down its local, negative z-axis).
  </div>
  <ul class="params">
    <li><span class="param-name">target</span> - Node to orient the camera towards</li>
    <li><span class="param-name">position</span> - Position of the camera node</li>
  </ul>
</div>