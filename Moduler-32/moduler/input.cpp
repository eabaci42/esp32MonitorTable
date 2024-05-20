#include "input.h"

// Pin Definitions
int upButtonPin = 25;
int downButtonPin = 26;
int stopButtonPin = 27;
int horizontalButtonPin = 14;
int verticalButtonPin = 13;
int startSwitchPin = 36;
int openCapSwitchPin = 39;
int closeCapSwitchPin = 34;
int ymaxSwitchPin = 35;
int verticalSwitchPin = 32;
int finalSwitchPin = 33;

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

void setupButtons() {
    ezButton* buttons[] = {&upButton, &downButton, &stopButton, &horizontalButton, &verticalButton,
                           &startSwitch, &openCapSwitch, &closeCapSwitch, &ymaxSwitch, &verticalSwitch, &finalSwitch};
    for (ezButton* button : buttons) {
        button->setDebounceTime(50);
    }
}

void allLoop() {
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

bool checkPressed(ezButton& button) {
    button.loop();
    return button.isPressed();
}
