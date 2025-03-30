#ifndef FSM_H
#define FSM_H

#include <FiniteStateMachine.h>

// FSM state object declaration
extern State START;
extern State OPENCAP;
extern State CLOSECAP;
extern State Y_RISING;
extern State Y_MIDDLE;
extern State Y_FALLING;
extern State YZ_VERTICAL;
extern State Z_VERTICAL;
extern State Z_RISING;
extern State Z_MIDDLE;
extern State Z_FALLING;
extern State PRESENTATION;
extern State UNDEFINED;
extern State ERROR;

// FSM instance
extern FiniteStateMachine fsm;

// Initialize FSM
void initFSM();

#endif // FSM_H 