#include "../../hal/input_hal.h"
#include "board.h"
#include <Arduino.h>

// Primary button: BOOT (GPIO 0, active LOW, internal pull-up).
// No secondary button on this board — INPUT_BTN_SECONDARY always returns false.
// BoardCaps.button_count = 1 tells shared code not to show secondary button UI.

void input_hal_init(void) {
    pinMode(BTN_BOOT, INPUT_PULLUP);
}

bool input_hal_is_held(InputButton btn) {
    switch (btn) {
    case INPUT_BTN_PRIMARY:
        return digitalRead(BTN_BOOT) == LOW;
    case INPUT_BTN_SECONDARY:
        return false;
    }
    return false;
}
