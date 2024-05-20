#ifndef INPUT_H
#define INPUT_H

#include <ezButton.h>

// Button and switch objects instantiation
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
