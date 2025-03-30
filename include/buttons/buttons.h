#ifndef BUTTONS_H
#define BUTTONS_H

#include <ezButton.h>

// Button declarations
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

// Initialize buttons
void initButtons();

// Update all buttons
void updateAllButtons();

// Check if a button is pressed
bool checkPressed(ezButton &button);

#endif // BUTTONS_H 