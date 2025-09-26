<!-- AUTO-GENERATED — do not edit. -->
# MouseEvent


Event representing mouse movement, clicks, or scroll input.
`MouseEvent` is dispatched when the mouse moves, a button is pressed or released, or the scroll wheel is used. Nodes can handle this event by overriding the `OnMouseEvent()` method. The event contains mouse position, scroll delta, button state, and event type.

```cpp
class MyNode : public gleam::Node {
public:
  auto OnMouseEvent(gleam::MouseEvent* event) -> void override {
    if (
      event->type == gleam::MouseEvent::Type::ButtonPressed &&
      event->button == gleam::MouseButton::Left
    ) {
      Select();
    }

    if (event->type == gleam::MouseEvent::Type::Moved) {
      UpdateCursor(event->position);
    }
  }
};
```
## Properties

<div class="property">
  <div class="definition">
    <span class="name">button</span> <span class="type">MouseButton</span>
  </div>
  <div class="description">
    Mouse button involved in the event (if any).
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">position</span> <span class="type">Vector2</span>
  </div>
  <div class="description">
    Current cursor position in window coordinates.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">scroll</span> <span class="type">Vector2</span>
  </div>
  <div class="description">
    Scroll delta since last event.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">type</span> <span class="type">MouseEvent::Type</span>
  </div>
  <div class="description">
    Mouse event type.
  </div>
</div>

## Functions

### `GetType()`
  - Returns event type.
