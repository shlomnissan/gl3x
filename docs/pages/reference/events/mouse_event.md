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
