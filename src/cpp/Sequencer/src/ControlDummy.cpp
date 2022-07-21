#include <iostream>

#include "Sequencer.hpp"
#include "ControlDummy.h"

ControlDummy::ControlDummy(
        unsigned char       *ptrInByte, 
        unsigned char       *ptrOutByte
    )
{
    // zweiter ansatz mit Step class als datenhalter für mealy automaten logik
    Sequence[0] = new Sequencer<ControlDummy>(this);
    Sequence[0]->AddStep(&ControlDummy::EnterA, &ControlDummy::MoveB);
    Sequence[0]->AddTransition(&ControlDummy::CanMoveA,1);
    Sequence[0]->AddTransition(&ControlDummy::CanMoveB,2);

    Sequence[0]->AddStep(&ControlDummy::EnterB, &ControlDummy::MoveB);
    Sequence[0]->AddTransition(&ControlDummy::CanMoveA, 0);

    Sequence[0]->AddStep(&ControlDummy::EnterA, &ControlDummy::MoveB);
    Sequence[0]->AddTransition(&ControlDummy::CanMoveB, 0);

    Sequence[0]->AddStep(&ControlDummy::RampUp, &ControlDummy::MoveB);
}

ControlDummy::~ControlDummy()
{
}

void ControlDummy::EnterA() {
    printf("Function Call: %s \n", __FUNCTION__);
}

void ControlDummy::EnterB() {
    printf("Function Call: %s \n", __FUNCTION__);
}

void ControlDummy::MoveA() {
    printf("Function Call: %s \n", __FUNCTION__);
}

void ControlDummy::MoveB(){
    printf("Function Call: %s \n", __FUNCTION__);
}

bool ControlDummy::CanMoveA() {
    int val = 0;
    printf("Function Call: %s \n", __FUNCTION__);
    std::cout << "Enter 0 to continue" << std::endl;
    std::cin >> val;
    return val == 0;
}

bool ControlDummy::CanMoveB(){
    int val = 0;
    printf("Function Call: %s \n", __FUNCTION__);
    std::cout << "Enter 1 to continue" << std::endl;
    std::cin >> val;
    return val != 0;
}

void ControlDummy::RampUp(){
    printf("Function Call: %s \n", __FUNCTION__);
}

void ControlDummy::RampDown(){
    printf("Function Call: %s \n", __FUNCTION__);
}
