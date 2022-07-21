#pragma once

#include <stddef.h>
#include "SequencerStep.hpp"

const int StepCount = 50;

template <class T>
struct Sequencer
{
private:
    T	*const _control;
    SequencerStep<T>* _steps[StepCount];
    
    int	_activeStep;

    int size() {
        return Size - 1;
    }

public:

    int			Size;

    Sequencer(T* control) : _control(control)
    {
        Size = 0;
        _activeStep = 0;

        for (int i = 0; i != StepCount; i++)
            _steps[i] = NULL; // new Step<T>();
    };

    void ResetSequencer(int stepNumber = 0)
    {
        _activeStep = stepNumber;
    }

    void AddStep(void(T:: * enterStep)(), void(T:: * stepAction)())
    {
        Size++;
        _steps[size()] = new SequencerStep<T>(_control);
        _steps[size()]->AddStep(enterStep, stepAction);
    }

    void AddTransition(bool(T::* exitStep)(), int transitionToStep) {
        _steps[size()]->AddTransition(exitStep, transitionToStep);
    }

    void Invoke()
    {
        if (_steps[_activeStep] == NULL)
            return;

        if (_steps[_activeStep]->Invoke())
            _activeStep++;
    }
};