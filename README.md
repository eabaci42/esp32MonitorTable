
# Finite State Machine Control System

This project implements a Finite State Machine (FSM) to control a multi-motor system with various buttons and switches using an ESP32 microcontroller. The system manages different states and transitions to perform complex operations, including cap manipulation and motor control.

## Table of Contents
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Pin Definitions](#pin-definitions)
- [Installation](#installation)
- [Usage](#usage)
- [Finite State Machine](#finite-state-machine)
- [State Functions](#state-functions)
- [Cap Manipulation Functions](#cap-manipulation-functions)
- [Utility Functions](#utility-functions)
- [Contributing](#contributing)
- [License](#license)

## Hardware Requirements
- ESP32 microcontroller
- Buttons and switches
- Motors
- Motor drivers
- Connecting wires
- Power supply

## Software Requirements
- Arduino IDE
- ezButton library
- FiniteStateMachine library

## Pin Definitions
| Component           | Pin Number |
|---------------------|------------|
| Up Button           | 25         |
| Down Button         | 26         |
| Stop Button         | 27         |
| Horizontal Button   | 14         |
| Vertical Button     | 12         |
| Start Switch        | 36         |
| Open Cap Switch     | 39         |
| Close Cap Switch    | 34         |
| Ymax Switch         | 35         |
| Vertical Switch     | 32         |
| Final Switch        | 33         |
| Main Motor Forward  | 23         |
| Main Motor Backward | 22         |
| Second Motor Forward| 3          |
| Second Motor Backward| 21        |
| Cap Motor Forward   | 19         |
| Cap Motor Backward  | 18         |

## Installation
1. Clone this repository to your local machine:
   \`\`\`sh
   git clone https://github.com/yourusername/fsm-control-system.git
   \`\`\`
2. Open the project in Arduino IDE.
3. Install the required libraries:
   - ezButton
   - FiniteStateMachine

4. Connect your ESP32 and upload the sketch.

## Usage
1. Set up the hardware as per the pin definitions.
2. Power on the system.
3. Monitor the serial output for debugging and state transitions.
4. Use the buttons and switches to control the state machine and perform operations.

## Finite State Machine
The FSM controls the state transitions based on button and switch inputs. The states include:
- START
- OPENCAP
- CLOSECAP
- Y_RISING
- Y_MIDDLE
- Y_FALLING
- YZ_VERTICAL
- Z_VERTICAL
- Z_RISING
- Z_MIDDLE
- Z_FALLING
- PRESENTATION
- UNDEFINED
- ERROR

## State Functions
### startState
Initial state that checks for the start conditions and transitions to OPENCAP state.
\`\`\`cpp
void startState();
\`\`\`

### openCapState
Handles the operation of opening the cap.
\`\`\`cpp
void openCapState();
\`\`\`

### closeCapState
Handles the operation of closing the cap.
\`\`\`cpp
void closeCapState();
\`\`\`

### yrisingState
Manages the Y-axis rising movement.
\`\`\`cpp
void yrisingState();
\`\`\`

### ymiddleState
Manages the Y-axis middle position.
\`\`\`cpp
void ymiddleState();
\`\`\`

### yfallingState
Manages the Y-axis falling movement.
\`\`\`cpp
void yfallingState();
\`\`\`

### yzverticalState
Handles the Y-Z axis vertical transition.
\`\`\`cpp
void yzverticalState();
\`\`\`

### zverticalState
Manages the Z-axis vertical position.
\`\`\`cpp
void zverticalState();
\`\`\`

### zrisingState
Handles the Z-axis rising movement.
\`\`\`cpp
void zrisingState();
\`\`\`

### zmiddleState
Manages the Z-axis middle position.
\`\`\`cpp
void zmiddleState();
\`\`\`

### zfallingState
Handles the Z-axis falling movement.
\`\`\`cpp
void zfallingState();
\`\`\`

### presentationState
State for presentation mode.
\`\`\`cpp
void presentationState();
\`\`\`

### undefinedState
Initial undefined state.
\`\`\`cpp
void undefinedState();
\`\`\`

### errorState
Handles error conditions.
\`\`\`cpp
void errorState();
\`\`\`

## Cap Manipulation Functions
### openCap
Function to open the cap.
\`\`\`cpp
bool openCap();
\`\`\`

### closeCap
Function to close the cap.
\`\`\`cpp
bool closeCap();
\`\`\`

## Utility Functions
### checkPressed
Checks if a button or switch is pressed.
\`\`\`cpp
bool checkPressed(ezButton &button);
\`\`\`

### allLoop
Loops through all buttons and switches.
\`\`\`cpp
void allLoop();
\`\`\`

### updateErrorMessage
Updates the error message.
\`\`\`cpp
void updateErrorMessage(const char *message);
\`\`\`

### forwardMotor
Moves a motor forward.
\`\`\`cpp
void forwardMotor(int pin1, int pin2);
\`\`\`

### backwardMotor
Moves a motor backward.
\`\`\`cpp
void backwardMotor(int pin1, int pin2);
\`\`\`

### stopMotor
Stops a motor.
\`\`\`cpp
void stopMotor(int pin1, int pin2);
\`\`\`

## Contributing
Contributions are welcome! Please fork this repository and submit a pull request with your improvements.

## License
This project is licensed under the MIT License. See the \`LICENSE\` file for details.
