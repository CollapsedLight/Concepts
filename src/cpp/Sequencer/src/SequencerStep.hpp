#pragma once

#include <stddef.h>

const int MaximumTransitions = 10;

template <class T>
struct SequencerStep
{
private:
    T *const _target;

    typedef void (T::* Transition)();
    typedef bool (T::* Action)();

    Transition	_fcEnter;
    Transition	_fcAction;

    Action	_fcExit[MaximumTransitions];
    int		_exitStep[MaximumTransitions];
    int		_transitionCounter = 0;

    bool	_stepActive;

public:

    SequencerStep(T* target) : _target(target)
    {
        _fcEnter	= NULL;
        _fcAction	= NULL;
        for (int i = 0; i < MaximumTransitions; i++) {
            _fcExit[i] = NULL;
        }
    };

    void AddStep(Transition enter, Transition step) {
        _fcEnter = enter;
        _fcAction = step;
    }

    void AddTransition(Action exit, int transitionToStep) {
        _fcExit[_transitionCounter] = exit;
        _exitStep[_transitionCounter] = transitionToStep;
        _transitionCounter++;
    }

    int Invoke()
    {
        if (!_stepActive)
        {
            (_target->*_fcEnter)();
            _stepActive = true;
            return 1;
        }
        
        (_target->*_fcAction)();
        
        for (int i = 0; i < MaximumTransitions; i++) {
            if ((_target->*_fcExit[i])()) {
                _stepActive = false;
                return _exitStep[i];
            }
        }
        return -1;
    }
};