#pragma once

#include <stdio.h>
#include "Sequencer.hpp"

class ControlDummy
{
private:
    void EnterA();
    void EnterB();
    void MoveA();
    void MoveB();
    bool CanMoveA();
    bool CanMoveB();
    void RampUp();
    void RampDown();


protected:

public:
    ControlDummy(
        unsigned char       *ptrInByte, 
        unsigned char       *ptrOutByte
    );
    virtual ~ControlDummy();

    Sequencer<ControlDummy>* Sequence[1];
};