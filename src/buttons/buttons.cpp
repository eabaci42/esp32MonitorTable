#include "../../include/buttons/buttons.h"
#include "../../include/config/pins.h"

// Button instances
ezButton upButton(UP_BUTTON_PIN);
ezButton downButton(DOWN_BUTTON_PIN);
ezButton stopButton(STOP_BUTTON_PIN);
ezButton horizontalButton(HORIZONTAL_BUTTON_PIN);
ezButton verticalButton(VERTICAL_BUTTON_PIN);
ezButton startSwitch(START_SWITCH_PIN);
ezButton openCapSwitch(OPEN_CAP_SWITCH_PIN);
ezButton closeCapSwitch(CLOSE_CAP_SWITCH_PIN);
ezButton ymaxSwitch(YMAX_SWITCH_PIN);
ezButton verticalSwitch(VERTICAL_SWITCH_PIN);
ezButton finalSwitch(FINAL_SWITCH_PIN);

// Initialize buttons with debounce setting
void initButtons() {
    ezButton *buttons[] = {
        &upButton, &downButton, &stopButton, &horizontalButton, &verticalButton,
        &startSwitch, &openCapSwitch, &closeCapSwitch, &ymaxSwitch, &verticalSwitch, &finalSwitch
    };
    
    for (ezButton *button : buttons) {
        button->setDebounceTime(50);
    }
}

// Update all buttons in the loop
void updateAllButtons() {
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

// Check if a button is pressed
bool checkPressed(ezButton &button) {
    button.loop();
    return button.isPressed();
} 