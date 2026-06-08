#include "../../hal/power_hal.h"
#include "board.h"
#include <Arduino.h>

// This board has no AXP2101 PMU and no battery management IC.
// The "power button" is the physical BOOT button (GPIO 0, active LOW).
// Battery functions return sentinel values — shared code checks
// BoardCaps.has_battery before displaying battery UI.

#define DEBOUNCE_MS  50
#define LONG_MS     1500

static bool     btn_prev       = false;
static bool     pressed_flag   = false;
static bool     long_flag      = false;
static bool     released_flag  = false;
static uint32_t press_start    = 0;
static bool     long_fired     = false;

void power_hal_init(void) {
    pinMode(BTN_BOOT, INPUT_PULLUP);
    Serial.println("Power HAL init OK (BOOT button, no PMU)");
}

void power_hal_tick(void) {
    bool held = (digitalRead(BTN_BOOT) == LOW);
    uint32_t now = millis();

    if (held && !btn_prev) {
        // Press edge
        press_start = now;
        long_fired  = false;
    }
    if (held && !long_fired && (now - press_start >= LONG_MS)) {
        long_flag  = true;
        long_fired = true;
    }
    if (!held && btn_prev) {
        // Release edge
        if (!long_fired) pressed_flag = true;   // short press
        released_flag = true;
    }
    btn_prev = held;
}

// No battery on this board.
int  power_hal_battery_pct(void)  { return -1; }
bool power_hal_is_charging(void)  { return false; }
bool power_hal_is_vbus_in(void)   { return true; }  // always USB-powered

bool power_hal_pwr_pressed(void) {
    if (pressed_flag)  { pressed_flag  = false; return true; }
    return false;
}
bool power_hal_pwr_long_pressed(void) {
    if (long_flag)     { long_flag     = false; return true; }
    return false;
}
bool power_hal_pwr_released(void) {
    if (released_flag) { released_flag = false; return true; }
    return false;
}
