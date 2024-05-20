#ifndef INPUT_H
#define INPUT_H

#include <ezButton.h>

// Pin Definitions
extern int upButtonPin;
extern int downButtonPin;
extern int stopButtonPin;
extern int horizontalButtonPin;
extern int verticalButtonPin;
extern int startSwitchPin;
extern int openCapSwitchPin;
extern int closeCapSwitchPin;
extern int ymaxSwitchPin;
extern int verticalSwitchPin;
extern int finalSwitchPin;

extern ezButton upButton;
extern ezButton downButton;
extern ezButton stopButton;
extern ezButton horizontalButton;
extern ezButton verticalButton;
extern ezButton startSwitch;
extern ezButton openCapSwitch;
extern ezButton closeCapSwitch;
extern ezButton ymaxSwitch;
extern ezButton verticalSwitch;
extern ezButton finalSwitch;

// Function Prototypes
void setupButtons();
void allLoop();
bool checkPressed(ezButton &button);

#endif // INPUT_H
