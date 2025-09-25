<!-- AUTO-GENERATED — do not edit. -->
# SceneEvent


Event representing a change in the scene graph hierarchy.
`SceneEvent` is dispatched when a node is added to or removed from the active scene. It contains a reference to the affected node and the type of change.

This event type is currently used internally by the active scene object to track hierarchy changes and **cannot be handled by individual nodes**.
## Constructors

### `SceneEvent()`
Constructs a SceneEvent.

## Properties

- `std::shared_ptr<Node> node`
  - Node that was added or removed.

- `SceneEvent::Type type`
  - Scene event type.

## Functions

### `GetType()`
  - Returns event type.
