#include "include/config/pins.h"
#include "include/buttons/buttons.h"
#include "include/motors/motors.h"
#include "include/cap/cap.h"
#include "include/utils/flags.h"
#include "include/states/fsm.h"
#include "include/states/states.h"

void setup() {
    Serial.begin(115200); // Start serial communication
    Serial.println("Setup basliyor");
    
    // Initialize buttons with debounce settings
    initButtons();
    
    // Initialize motor pins
    initMotors();
    
    // Initialize FSM and transition to start state
    initFSM();
    
    Serial.println("Setup bitti");
}

void loop() {
    // Update all buttons
    updateAllButtons();
    
    // Update FSM
    fsm.update();
} 