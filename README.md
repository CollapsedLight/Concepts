# Concepts

A place for my ideas and concepts.

## Sequencer
Functional approach to creating step chain.
A sequence can be registered any where but at compile time. It can be executed in a loop and will transition when provided transitional function allows it to.
It can handle multiple transitions and out going steps.
This is a rough concept and would need more fine tuining. The appending of a transition stel is not realy nice, also the application does not properly check for `NULL`.

```cpp
Sequence[0] = new Sequencer<ControlDummy>(this);
Sequence[0]->AddStep(&ControlDummy::EnterA, &ControlDummy::MoveB);
Sequence[0]->AddTransition(&ControlDummy::CanMoveA,1); // Transition to step 1
Sequence[0]->AddTransition(&ControlDummy::CanMoveB,2); // Transition to step 2
```