#include "../../include/utils/flags.h"
#include <Arduino.h>

// Flag variables initialization
bool startFlag = true;    // Flag to indicate if the start has been initiated
bool finalFlag = false;   // Flag to indicate if the final state is reached
bool stopFlag = false;    // Flag to indicate if stop is pressed
bool errorFlag = false;   // Flag to indicate if error state
bool openCapFlag = false; // Flag to indicate if the cap is open
bool closeCapFlag = true; // Flag to indicate if the cap is closed
bool oneFlag = true;      // Flag to indicate if one time running action

// Global error message buffer
char errorMessage[8];

// Function to update the error message in the global buffer
void updateErrorMessage(const char *message) {
    // Safely format and store the message, ensuring no overflow
    snprintf(errorMessage, sizeof(errorMessage), "%s", message);
} 