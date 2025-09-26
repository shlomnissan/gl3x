<!-- AUTO-GENERATED — do not edit. -->
# KeyboardEvent


Event representing a keyboard key press or release.
`KeyboardEvent` is dispatched when a key is pressed or released. Nodes can handle this event by overriding the `OnKeyboardEvent()` method. The event contains both the key involved and the type of interaction.

```cpp
class MyNode : public gleam::Node {
public:
  auto OnKeyboardEvent(gleam::KeyboardEvent* event) -> void override {
    if (event->type == gleam::KeyboardEvent::Type::Pressed) {
      if (event->key == gleam::Key::Sapce) {
        Jump();
        event->handled = true; // stop propagation
      }
    }
  }
};
```
## Properties

<div class="property">
  <div class="definition">
    <span class="name">key</span> <span class="type">Key</span>
  </div>
  <div class="description">
    Key code associated with the event.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">type</span> <span class="type">KeyboardEvent::Type</span>
  </div>
  <div class="description">
    Keyboard event type.
  </div>
</div>

## Functions

### `GetType()`
  - Returns event type.
