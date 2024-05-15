#include <ezButton.h>
#include <FiniteStateMachine.h>

///////////////////////////////////////////
//              Navigation               //
///////////////////////////////////////////

// [1] Pin Definitions and Button/Switch Objects
//     - Pin numbers and initialization of ezButton objects.

// [2] Flags
//     - Flag variables for state transitions and conditions.

// [3] Finite State Machine Setup
//     - State function prototypes and definitions.
//     - Initialization of the FiniteStateMachine object with state declarations.

// [4] Setup and Loop Functions
//     - Arduino's setup() and loop() functions.
//     - Initialization of serial communication, debounce settings for buttons.
//     - FSM transition to the start state.

// [5] State Functions Definitions
//     - Definitions of functions for various states like startState, openCapState, closeCapState, etc.

// [6] Cap Manipulation Functions
//     - Functions to open and close the cap, managing cap-related flags.

// [7] Utility Function
//      - Function to check if a button or switch is pressed.
//      - Function to change error log message

///////////////////////////////////////////

///////////////////////////////////////////////////
// [1] Pin Definitions and Button/Switch Objects //
///////////////////////////////////////////////////

// Button and switch pin definitions
int upButtonPin = 25;         // Up button
int downButtonPin = 26;       // Down button
int stopButtonPin = 27;       // Stop button
int horizontalButtonPin = 14; // Horizontal button
int verticalButtonPin = 12;   // Vertical button
int startSwitchPin = 36;      // Start switch
int openCapSwitchPin = 39;    // Open cap switch
int closeCapSwitchPin = 34;   // Close cap switch
int ymaxSwitchPin = 35;       // Ymax switch
int verticalSwitchPin = 32;   // Vertical cap switch
int finalSwitchPin = 33;      // Additional horizontal switch

// Button and switch objects instantiation
ezButton upButton(upButtonPin);
ezButton downButton(downButtonPin);
ezButton stopButton(stopButtonPin);
ezButton horizontalButton(horizontalButtonPin);
ezButton verticalButton(verticalButtonPin);
ezButton startSwitch(startSwitchPin);
ezButton openCapSwitch(openCapSwitchPin);
ezButton closeCapSwitch(closeCapSwitchPin);
ezButton ymaxSwitch(ymaxSwitchPin);
ezButton verticalSwitch(verticalSwitchPin);
ezButton finalSwitch(finalSwitchPin);

int mainMotorForwardPin = 23;
int mainMotorBackwardPin = 22;
int secondMotorForwardPin = 3;
int secondMotorBackwardPin = 21;
int capMotorForwardPin = 19;
int capMotorBackwardPin = 18;

//////////////////////////////////////////////
// [2] Flags                                //
//////////////////////////////////////////////

// Flag variables to track state transitions and conditions
bool startFlag = true;    // Flag to indicate if the start has been initiated
bool finalFlag = false;   // Flag to indicate if the final state is reached
bool stopFlag = false;    // Flag  to indicate if the stop
bool errorFlag = false;   // Flag to indicate if error state
bool openCapFlag = false; // Flag to indicate if the cap is open
bool closeCapFlag = true; // Flag to indicate if the cap is closed
bool oneFlag = true;      // Flag to indicate if one time running action

// Global error message buffer
char errorMessage[8];

//////////////////////////////////////////////
// [3] Finite State Machine Setup           //
//////////////////////////////////////////////

// Utility Function prototypes
bool checkPressed(ezButton &button);
void allLoop();
void updateErrorMessage(const char *message);
bool openCap();
bool closeCap();
void forwardMotor(int pin1, int pin2);
void backwardMotor(int pin1, int pin2);
void stopMotor(int pin1, int pin2);

// State function prototypes
void startState();
void openCapState();
void closeCapState();
void yrisingState();
void ymiddleState();
void yfallingState();
void yzverticalState();
void zverticalState();
void zrisingState();
void zmiddleState();
void zfallingState();
void presentationState();
void undefinedState();
void errorState();

// State declarations
State START = State(startState);     // Start of the machine
State OPENCAP = State(openCapState); // Cap operations
State CLOSECAP = State(closeCapState);
State Y_RISING = State(yrisingState); // Y-axis movement states
State Y_MIDDLE = State(ymiddleState);
State Y_FALLING = State(yfallingState);
State YZ_VERTICAL = State(yzverticalState);
State Z_VERTICAL = State(zverticalState);
State Z_RISING = State(zrisingState); // Z-axis movement states
State Z_MIDDLE = State(zmiddleState);
State Z_FALLING = State(zfallingState);
State PRESENTATION = State(presentationState); // Presentation mode
State UNDEFINED = State(undefinedState);       // Initial undefined state
State ERROR = State(errorState);               // Error handling state

FiniteStateMachine fsm(UNDEFINED); // Initialize FSM with an undefined state

//////////////////////////////////////////////
// [4] Setup and Loop Functions             //
//////////////////////////////////////////////

void setup()
{
    Serial.begin(115200); // Start serial communication
    Serial.println("Setup basliyor");
    // Set debounce time for all buttons
    ezButton *buttons[] = {&upButton, &downButton, &stopButton, &horizontalButton, &verticalButton,
                           &startSwitch, &openCapSwitch, &closeCapSwitch, &ymaxSwitch, &verticalSwitch, &finalSwitch};
    for (ezButton *button : buttons)
    {
        button->setDebounceTime(50);
    }

    // Set motor pins as output
    int motorPins[] = {mainMotorForwardPin, mainMotorBackwardPin, secondMotorForwardPin, secondMotorBackwardPin, capMotorForwardPin, capMotorBackwardPin};
    for (int pin : motorPins)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH); // Assume HIGH means motors are stopped
    }
    Serial.println("Setup bitti");
    fsm.transitionTo(START); // Transition FSM to start state
}
/*
void setup()
{
    Serial.begin(115200); // Start serial communication

    // Set debounce time for buttons
    upButton.setDebounceTime(50);
    downButton.setDebounceTime(50);
    stopButton.setDebounceTime(50);
    horizontalButton.setDebounceTime(50);
    verticalButton.setDebounceTime(50);
    startSwitch.setDebounceTime(50);
    openCapSwitch.setDebounceTime(50);
    closeCapSwitch.setDebounceTime(50);
    ymaxSwitch.setDebounceTime(50);
    verticalSwitch.setDebounceTime(50);
    finalSwitch.setDebounceTime(50);

    // Set motor pins as output
    pinMode(mainMotorForwardPin, OUTPUT);
    pinMode(mainMotorBackwardPin, OUTPUT);
    pinMode(secondMotorForwardPin, OUTPUT);
    pinMode(secondMotorBackwardPin, OUTPUT);
    pinMode(capMotorForwardPin, OUTPUT);
    pinMode(capMotorBackwardPin, OUTPUT);

    // Set all motor pins to HIGH (assuming HIGH means motors are stopped)
    digitalWrite(mainMotorForwardPin, HIGH);
    digitalWrite(mainMotorBackwardPin, HIGH);
    digitalWrite(secondMotorForwardPin, HIGH);
    digitalWrite(secondMotorBackwardPin, HIGH);
    digitalWrite(capMotorForwardPin, HIGH);
    digitalWrite(capMotorBackwardPin, HIGH);

    fsm.transitionTo(START); // Transition FSM to start state
}
*/
void loop()
{
    allLoop();    // Call the loop function for all buttons
    fsm.update(); // Update FSM
}

//////////////////////////////////////////////
// [5] State Functions Definitions          //
//////////////////////////////////////////////

void startState()
{
    Serial.println("Start state");
    // Check button state and make transitions
    if (checkPressed(upButton))
    {
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(OPENCAP); // Transition to Open Cap state when UpButton is pressed
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            fsm.transitionTo(START);
        }
    }
}

void openCapState()
{
    if (startFlag)
    {
        // Check if the function is being called with proper authorization
        Serial.println("Open Cap State");
        if (!openCapFlag)
        {
            // Check if the cap is not already open
            if (openCap())
            { // Perform cap opening operation
                openCapFlag = true;
                closeCapFlag = false;
                fsm.transitionTo(Y_RISING); // Transition to Y-axis rising state after cap opening
            }
            else
            {
                // Transition to error state if cap opening operation fails
                fsm.transitionTo(ERROR);
                updateErrorMessage("E02X003"); // E02X003 -> Error occurred during cap opening operation
            }
        }
        else
        {
            // Transition to error state if openCapFlag is in an unexpected state
            fsm.transitionTo(ERROR);
            updateErrorMessage("E02X002"); // E02X002 -> openCapFlag has an unexpected value
        }
    }
    else
    {
        // Transition to error state if the function is called without proper authorization
        fsm.transitionTo(ERROR);
        updateErrorMessage("E02X001"); // E02X001 -> Unauthorized access to openCapState function
    }
}

void closeCapState()
{
    if (finalFlag)
    {
        // Check if the function is being called with proper authorization
        Serial.println("Close Cap State");
        if (!closeCapFlag)
        {
            // Check if the cap is not already closed
            if (closeCap())
            { // Perform cap closing operation
                closeCapFlag = true;
                openCapFlag = false;
                fsm.transitionTo(START); // Transition to START state after cap closing
            }
            else
            {
                // Transition to error state if cap closing operation fails
                fsm.transitionTo(ERROR);
                updateErrorMessage("E03X003"); // E03X003 -> Error occurred during cap closing operation
            }
        }
        else
        {
            // Transition to error state if closeCapFlag is in an unexpected state
            fsm.transitionTo(ERROR);
            updateErrorMessage("E03X002"); // E03X002 -> closeCapFlag has an unexpected value
        }
    }
    else
    {
        // Transition to error state if the function is called without proper authorization
        fsm.transitionTo(ERROR);
        updateErrorMessage("E03X001"); // E03X001 -> Unauthorized access to closeCapState function
    }
}

void yrisingState()
{
    Serial.println("Y Rising State");
    if (checkPressed(ymaxSwitch))
    {
        stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
        oneFlag = true;
        fsm.transitionTo(YZ_VERTICAL);
    }
    else if (checkPressed(stopButton))
    {
        stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
        startFlag = false;
        finalFlag = false;
        stopFlag = true;
        oneFlag = true;
        fsm.transitionTo(Y_MIDDLE);
    }
    else if (checkPressed(downButton))
    {
        stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_FALLING);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            forwardMotor(mainMotorForwardPin, mainMotorBackwardPin);
        }
    }
}

void ymiddleState()
{ // her up ya da down olan yerde final/start mı değişsem?
    Serial.println("Y Middle State");
    if (checkPressed(upButton))
    {
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_RISING);
    }
    else if (checkPressed(downButton))
    {
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_FALLING);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            fsm.transitionTo(Y_MIDDLE);
        }
    }
}

void yfallingState()
{
    Serial.println("Y Falling State");
    if (checkPressed(startSwitch))
    {
        stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
        oneFlag = true;
        fsm.transitionTo(CLOSECAP);
    }
    else if (checkPressed(upButton))
    {
        stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_RISING);
    }
    else if (checkPressed(stopButton))
    {
        stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
        startFlag = false;
        finalFlag = false;
        stopFlag = true;
        oneFlag = true;
        fsm.transitionTo(Y_MIDDLE);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            backwardMotor(mainMotorForwardPin, mainMotorBackwardPin);
        }
    }
}

void yzverticalState()
{
    Serial.println("YZ Vertical State");
    if (startFlag)
    {
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    }
    else if (finalFlag)
    {
        oneFlag = true;
        fsm.transitionTo(Y_FALLING);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        }
    }
}
void zverticalState()
{
    Serial.println("Z Vertical State");
    if (checkPressed(upButton))
    {
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    }
    else if (checkPressed(downButton))
    {
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_FALLING);
    }
    else if (checkPressed(horizontalButton))
    {
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        }
    }
}

void zrisingState()
{
    Serial.println("Z Rising State");
    if (checkPressed(finalSwitch))
    {
        stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        oneFlag = true;
        fsm.transitionTo(PRESENTATION);
    }
    else if (checkPressed(stopButton))
    {
        stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        startFlag = false;
        finalFlag = false;
        stopFlag = true;
        oneFlag = true;
        fsm.transitionTo(Z_MIDDLE);
    }
    else if (checkPressed(downButton))
    {
        stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    }
    else if (checkPressed(verticalButton))
    {
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            forwardMotor(secondMotorForwardPin, secondMotorBackwardPin);
        }
    }
}
void zmiddleState()
{
    Serial.println("Z Middle State");
    if (checkPressed(upButton))
    {
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    }
    else if (checkPressed(downButton))
    {
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    }
    else if (checkPressed(verticalButton))
    {
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    }
    else if (checkPressed(horizontalButton))
    {
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            fsm.transitionTo(Z_MIDDLE);
        }
    }
}
void zfallingState()
{
    Serial.println("Z Falling State");
    if (checkPressed(verticalSwitch))
    {
        stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        oneFlag = true;
        if (finalFlag)
            fsm.transitionTo(YZ_VERTICAL);
        else
            fsm.transitionTo(Z_VERTICAL);
    }
    else if (checkPressed(upButton))
    {
        stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    }
    else if (checkPressed(stopButton))
    {
        stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        startFlag = false;
        finalFlag = false;
        stopFlag = true;
        oneFlag = true;
        fsm.transitionTo(Z_MIDDLE);
    }
    else if (checkPressed(horizontalButton))
    {
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            backwardMotor(secondMotorForwardPin, secondMotorBackwardPin);
        }
    }
}
void presentationState()
{
    Serial.println("Presentation State");
    if (checkPressed(downButton))
    {
        stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    }
    else if (checkPressed(verticalButton))
    {
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    }
    else
    {
        if (oneFlag)
        {
            oneFlag = false;
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
        }
    }
}
void undefinedState() { ; }
void errorState() { ; }

//////////////////////////////////////////////
// [6] Cap Manipulation Functions           //
//////////////////////////////////////////////

bool openCap()
{
    while (closeCapFlag)
    {
        if (oneFlag)
        {
            oneFlag = false;
            forwardMotor(capMotorForwardPin, capMotorBackwardPin);
        }
        if (checkPressed(openCapSwitch))
        {
            stopMotor(capMotorForwardPin, capMotorBackwardPin);
            oneFlag = true;
            return true; // Return True
        }
    }
    return false;
}

bool closeCap()
{
    while (openCapFlag)
    {
        if (oneFlag)
        {
            oneFlag = false;
            backwardMotor(capMotorForwardPin, capMotorBackwardPin);
        }
        if (checkPressed(closeCapSwitch))
        {
            stopMotor(capMotorForwardPin, capMotorBackwardPin);
            oneFlag = true;
            return true; // Return True
        }
    }
    return false;
}

//////////////////////////////////////////////
// [7] Utility Function                     //
//////////////////////////////////////////////

// Function to check if a button or switch is pressed
bool checkPressed(ezButton &button)
{
    button.loop();
    return button.isPressed();
}

void allLoop()
{
    upButton.loop();
    downButton.loop();
    stopButton.loop();
    horizontalButton.loop();
    verticalButton.loop();
    startSwitch.loop();
    openCapSwitch.loop();
    closeCapSwitch.loop();
    ymaxSwitch.loop();
    verticalSwitch.loop();
    finalSwitch.loop();
}

// Function to update the error message in the global buffer
void updateErrorMessage(const char *message)
{
    // Safely format and store the message, ensuring no overflow
    snprintf(errorMessage, sizeof(errorMessage), "%s", message);
}

void forwardMotor(int pin1, int pin2) // Function to move motor forward
{
    digitalWrite(pin1, LOW);  // Set pin1 LOW     - Enable
    digitalWrite(pin2, HIGH); // Set pin2 HIGH    - Disable
    Serial.println("forwardMotor");
}

void backwardMotor(int pin1, int pin2) // Function to move motor backward
{
    digitalWrite(pin1, HIGH); // Set pin1 HIGH    - Disable
    digitalWrite(pin2, LOW);  // Set pin2 LOW     - Enable
    Serial.println("backwardMotor");
}

void stopMotor(int pin1, int pin2) // Function to stop motor
{
    digitalWrite(pin1, HIGH); // Set pin1 HIGH    - Disable
    digitalWrite(pin2, HIGH); // Set pin2 HIGH    - Disable
    Serial.println("backwardMotor");
}