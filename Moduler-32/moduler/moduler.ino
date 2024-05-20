    #include <Arduino.h>
    #include <FiniteStateMachine.h>
    #include "input.h"
    #include "output.h"

    //////////////////////////////////////////////
    // [2] Flags                                //
    //////////////////////////////////////////////

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
    void updateErrorMessage(const char *message);
    bool openCap();
    bool closeCap();

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

    void setup() {
        Serial.begin(115200); // Start serial communication
        Serial.println("Setup başlıyor");

        setupButtons();
        setupMotors();

        Serial.println("Setup bitti");
        fsm.transitionTo(START); // Transition FSM to start state
    }

    void loop() {
        allLoop();    // Call the loop function for all buttons
        fsm.update(); // Update FSM
    }

    //////////////////////////////////////////////
    // [5] State Functions Definitions          //
    //////////////////////////////////////////////

    void startState() {
        Serial.println("Start state");
        // Check button state and make transitions
        if (checkPressed(upButton)) {
            startFlag = true;
            finalFlag = false;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(OPENCAP); // Transition to Open Cap state when UpButton is pressed
        } else {
            if (oneFlag) {
                oneFlag = false;
                fsm.transitionTo(START);
            }
        }
    }

    void openCapState() {
        if (startFlag) {
            // Check if the function is being called with proper authorization
            Serial.println("Open Cap State");
            if (!openCapFlag) {
                // Check if the cap is not already open
                if (openCap()) { // Perform cap opening operation
                    openCapFlag = true;
                    closeCapFlag = false;
                    fsm.transitionTo(Y_RISING); // Transition to Y-axis rising state after cap opening
                } else {
                    // Transition to error state if cap opening operation fails
                    fsm.transitionTo(ERROR);
                    updateErrorMessage("E02X003"); // E02X003 -> Error occurred during cap opening operation
                }
            } else {
                // Transition to error state if openCapFlag is in an unexpected state
                fsm.transitionTo(ERROR);
                updateErrorMessage("E02X002"); // E02X002 -> openCapFlag has an unexpected value
            }
        } else {
            // Transition to error state if the function is called without proper authorization
            fsm.transitionTo(ERROR);
            updateErrorMessage("E02X001"); // E02X001 -> Unauthorized access to openCapState function
        }
    }

    void closeCapState() {
        if (finalFlag) {
            // Check if the function is being called with proper authorization
            Serial.println("Close Cap State");
            if (!closeCapFlag) {
                // Check if the cap is not already closed
                if (closeCap()) { // Perform cap closing operation
                    closeCapFlag = true;
                    openCapFlag = false;
                    fsm.transitionTo(START); // Transition to START state after cap closing
                } else {
                    // Transition to error state if cap closing operation fails
                    fsm.transitionTo(ERROR);
                    updateErrorMessage("E03X003"); // E03X003 -> Error occurred during cap closing operation
                }
            } else {
                // Transition to error state if closeCapFlag is in an unexpected state
                fsm.transitionTo(ERROR);
                updateErrorMessage("E03X002"); // E03X002 -> closeCapFlag has an unexpected value
            }
        } else {
            // Transition to error state if the function is called without proper authorization
            fsm.transitionTo(ERROR);
            updateErrorMessage("E03X001"); // E03X001 -> Unauthorized access to closeCapState function
        }
    }

    void yrisingState() {
        Serial.println("Y Rising State");
        if (checkPressed(ymaxSwitch)) {
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            oneFlag = true;
            fsm.transitionTo(YZ_VERTICAL);
        } else if (checkPressed(stopButton)) {
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            startFlag = false;
            finalFlag = false;
            stopFlag = true;
            oneFlag = true;
            fsm.transitionTo(Y_MIDDLE);
        } else if (checkPressed(downButton)) {
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            startFlag = false;
            finalFlag = true;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Y_FALLING);
        } else {
            if (oneFlag) {
                oneFlag = false;
                forwardMotor(mainMotorForwardPin, mainMotorBackwardPin);
            }
        }
    }

    void ymiddleState() {
        Serial.println("Y Middle State");
        if (checkPressed(upButton)) {
            startFlag = true;
            finalFlag = false;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Y_RISING);
        } else if (checkPressed(downButton)) {
            startFlag = false;
            finalFlag = true;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Y_FALLING);
        } else {
            if (oneFlag) {
                oneFlag = false;
                fsm.transitionTo(Y_MIDDLE);
            }
        }
    }

    void yfallingState() {
        Serial.println("Y Falling State");
        if (checkPressed(startSwitch)) {
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            oneFlag = true;
            fsm.transitionTo(CLOSECAP);
        } else if (checkPressed(upButton)) {
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            startFlag = true;
            finalFlag = false;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Y_RISING);
        } else if (checkPressed(stopButton)) {
            stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
            startFlag = false;
            finalFlag = false;
            stopFlag = true;
            oneFlag = true;
            fsm.transitionTo(Y_MIDDLE);
        } else {
            if (oneFlag) {
                oneFlag = false;
                backwardMotor(mainMotorForwardPin, mainMotorBackwardPin);
            }
        }
    }

    void yzverticalState() {
        Serial.println("YZ Vertical State");
        if (startFlag) {
            oneFlag = true;
            fsm.transitionTo(Z_RISING);
        } else if (finalFlag) {
            oneFlag = true;
            fsm.transitionTo(Y_FALLING);
        } else {
            if (oneFlag) {
                oneFlag = false;
                stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
                stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            }
        }
    }

    void zverticalState() {
        Serial.println("Z Vertical State");
        if (checkPressed(upButton)) {
            startFlag = true;
            finalFlag = false;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Z_RISING);
        } else if (checkPressed(downButton)) {
            startFlag = false;
            finalFlag = true;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Y_FALLING);
        } else if (checkPressed(horizontalButton)) {
            oneFlag = true;
            fsm.transitionTo(Z_RISING);
        } else {
            if (oneFlag) {
                oneFlag = false;
                stopMotor(mainMotorForwardPin, mainMotorBackwardPin);
                stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            }
        }
    }

    void zrisingState() {
        Serial.println("Z Rising State");
        if (checkPressed(finalSwitch)) {
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            oneFlag = true;
            fsm.transitionTo(PRESENTATION);
        } else if (checkPressed(stopButton)) {
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            startFlag = false;
            finalFlag = false;
            stopFlag = true;
            oneFlag = true;
            fsm.transitionTo(Z_MIDDLE);
        } else if (checkPressed(downButton)) {
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            startFlag = false;
            finalFlag = true;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Z_FALLING);
        } else if (checkPressed(verticalButton)) {
            oneFlag = true;
            fsm.transitionTo(Z_FALLING);
        } else {
            if (oneFlag) {
                oneFlag = false;
                forwardMotor(secondMotorForwardPin, secondMotorBackwardPin);
            }
        }
    }

    void zmiddleState() {
        Serial.println("Z Middle State");
        if (checkPressed(upButton)) {
            startFlag = true;
            finalFlag = false;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Z_RISING);
        } else if (checkPressed(downButton)) {
            startFlag = false;
            finalFlag = true;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Z_FALLING);
        } else if (checkPressed(verticalButton)) {
            oneFlag = true;
            fsm.transitionTo(Z_FALLING);
        } else if (checkPressed(horizontalButton)) {
            oneFlag = true;
            fsm.transitionTo(Z_RISING);
        } else {
            if (oneFlag) {
                oneFlag = false;
                fsm.transitionTo(Z_MIDDLE);
            }
        }
    }

    void zfallingState() {
        Serial.println("Z Falling State");
        if (checkPressed(verticalSwitch)) {
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            oneFlag = true;
            if (finalFlag)
                fsm.transitionTo(YZ_VERTICAL);
            else
                fsm.transitionTo(Z_VERTICAL);
        } else if (checkPressed(upButton)) {
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            startFlag = true;
            finalFlag = false;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Z_RISING);
        } else if (checkPressed(stopButton)) {
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            startFlag = false;
            finalFlag = false;
            stopFlag = true;
            oneFlag = true;
            fsm.transitionTo(Z_MIDDLE);
        } else if (checkPressed(horizontalButton)) {
            oneFlag = true;
            fsm.transitionTo(Z_RISING);
        } else {
            if (oneFlag) {
                oneFlag = false;
                backwardMotor(secondMotorForwardPin, secondMotorBackwardPin);
            }
        }
    }

    void presentationState() {
        Serial.println("Presentation State");
        if (checkPressed(downButton)) {
            stopMotor(secondMotorForwardPin, secondMotorBackwardPin);
            startFlag = false;
            finalFlag = true;
            stopFlag = false;
            oneFlag = true;
            fsm.transitionTo(Z_FALLING);
        } else if (checkPressed(verticalButton)) {
            oneFlag = true;
            fsm.transitionTo(Z_FALLING);
        } else {
            if (oneFlag) {
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

    bool openCap() {
        while (closeCapFlag) {
            if (oneFlag) {
                oneFlag = false;
                forwardMotor(capMotorForwardPin, capMotorBackwardPin);
            }
            if (checkPressed(openCapSwitch)) {
                stopMotor(capMotorForwardPin, capMotorBackwardPin);
                oneFlag = true;
                return true; // Return True
            }
        }
        return false;
    }

    bool closeCap() {
        while (openCapFlag) {
            if (oneFlag) {
                oneFlag = false;
                backwardMotor(capMotorForwardPin, capMotorBackwardPin);
            }
            if (checkPressed(closeCapSwitch)) {
                stopMotor(capMotorForwardPin, capMotorBackwardPin);
                oneFlag = true;
                return true; // Return True
            }
        }
        return false;
    }

    void updateErrorMessage(const char *message) {
        // Safely format and store the message, ensuring no overflow
        snprintf(errorMessage, sizeof(errorMessage), "%s", message);
    }
