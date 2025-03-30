#include "../../include/states/fsm.h"
#include "../../include/states/states.h"

// State declarations with their corresponding functions
State START = State(startState);
State OPENCAP = State(openCapState);
State CLOSECAP = State(closeCapState);
State Y_RISING = State(yrisingState);
State Y_MIDDLE = State(ymiddleState);
State Y_FALLING = State(yfallingState);
State YZ_VERTICAL = State(yzverticalState);
State Z_VERTICAL = State(zverticalState);
State Z_RISING = State(zrisingState);
State Z_MIDDLE = State(zmiddleState);
State Z_FALLING = State(zfallingState);
State PRESENTATION = State(presentationState);
State UNDEFINED = State(undefinedState);
State ERROR = State(errorState);

// Initialize FSM with an undefined state
FiniteStateMachine fsm(UNDEFINED);

// Initialize FSM and set it to START state
void initFSM() {
    fsm.transitionTo(START);
} 