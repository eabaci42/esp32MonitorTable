#ifndef FLAGS_H
#define FLAGS_H

// Global flag declarations
extern bool startFlag;    // Flag to indicate if the start has been initiated
extern bool finalFlag;    // Flag to indicate if the final state is reached
extern bool stopFlag;     // Flag to indicate if stop is pressed
extern bool errorFlag;    // Flag to indicate if error state
extern bool openCapFlag;  // Flag to indicate if the cap is open
extern bool closeCapFlag; // Flag to indicate if the cap is closed
extern bool oneFlag;      // Flag to indicate if one time running action

// Global error message buffer
extern char errorMessage[8];

// Function to update the error message in the global buffer
void updateErrorMessage(const char *message);

#endif // FLAGS_H 