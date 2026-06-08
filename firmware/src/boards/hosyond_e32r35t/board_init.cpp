#include "board.h"
#include <Arduino.h>

// Early board bring-up. On this board there is no shared I2C bus to start
// (no PMU, no IMU, no I2C touch controller — everything is SPI). The RGB
// LED is set to OFF here so it doesn't glow on boot; the BLE/status logic
// later drives it to reflect connection state.
extern "C" void board_init(void) {
    // RGB LED off (common anode: HIGH = off)
    pinMode(LED_R, OUTPUT); digitalWrite(LED_R, HIGH);
    pinMode(LED_G, OUTPUT); digitalWrite(LED_G, HIGH);
    pinMode(LED_B, OUTPUT); digitalWrite(LED_B, HIGH);

    // Backlight off until display_hal_begin() brings the panel up cleanly.
    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, LOW);
}
