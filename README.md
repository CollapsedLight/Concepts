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

## bitIO
The idea is to store all data that an io bit might have like falling or raising edges into one byte instead of using a byte for each boolean value.
The function is slower then fully compiler optimized equivalent that only uses `bool` but it requeres only one byte. It has only limited use cases as memory is a non issue these days.

Use the provided define `INPUT` for nameifing the bit.

```cpp
auto io = INPUT(test);
```

## Alarm
Create a stack to save active errors and warning.
