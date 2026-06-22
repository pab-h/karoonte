#include "init.hpp"

#include <Arduino.h>

#include "app/pins.hpp"

#include "keyboard/button/button.hpp"
#include "keyboard/types/types.hpp"

using namespace keyboard::types;

namespace keyboard {

    static ButtonData key_A = { 'A', 0 };
    static ButtonData key_B = { 'B', 0 };
    static ButtonData key_C = { 'C', 0 };
    static ButtonData key_D = { 'D', 0 };

    void init() {

        pinMode(BUTTON_A_PIN, INPUT);
        pinMode(BUTTON_B_PIN, INPUT);
        pinMode(BUTTON_C_PIN, INPUT);
        pinMode(BUTTON_D_PIN, INPUT);

        attachInterruptArg(
            digitalPinToInterrupt(BUTTON_A_PIN), 
            button::button_ISR, 
            &key_A, 
            RISING
        );
        attachInterruptArg(
            digitalPinToInterrupt(BUTTON_B_PIN), 
            button::button_ISR, 
            &key_B, 
            RISING
        );
        attachInterruptArg(
            digitalPinToInterrupt(BUTTON_C_PIN), 
            button::button_ISR, 
            &key_C, 
            RISING
        );
        attachInterruptArg(
            digitalPinToInterrupt(BUTTON_D_PIN), 
            button::button_ISR, 
            &key_D, 
            RISING
        );

    }
}