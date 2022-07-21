#pragma once

const int StepCount = 50;

template <class T>
struct SimpleSequencer
{
private:
    T* _control;
    typedef void (T::* StepFunction)();

public:
    StepFunction Step[StepCount];

    SimpleSequencer(T* control) : _control(control)
    {
        for (int i = 0; i != StepCount; i++)
            Step[i] = 0;
    };

    void Invoke(int stepNumber)
    {
        if (Step[stepNumber] != NULL)
            (_control->*Step[stepNumber])();
    }
};

