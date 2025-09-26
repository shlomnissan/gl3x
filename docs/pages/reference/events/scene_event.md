<!-- AUTO-GENERATED — do not edit. -->
# SceneEvent


Event representing a change in the scene graph hierarchy.
`SceneEvent` is dispatched when a node is added to or removed from the active scene. It contains a reference to the affected node and the type of change.

This event type is currently used internally by the active scene object to track hierarchy changes and **cannot be handled by individual nodes**.
## Constructors

### `SceneEvent()`
Constructs a SceneEvent.

## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">node</span> <span class="type">std::shared_ptr&lt;Node&gt;</span>
  ```cpp
  std::shared_ptr<Node> node 
  ```
  </div>
  <div class="description">
    Node that was added or removed.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">type</span> <span class="type">SceneEvent::Type</span>
  ```cpp
  SceneEvent::Type type 
  ```
  </div>
  <div class="description">
    Scene event type.
  </div>
</div>

## Functions

### `GetType()`
  - Returns event type.
