#include "../../hal/touch_hal.h"
#include "board.h"
#include <Arduino.h>
#include <TFT_eSPI.h>

// XPT2046 resistive touch is driven through TFT_eSPI's built-in touch
// support (TOUCH_CS defined in build_flags). The touch shares the display
// SPI bus — TFT_eSPI handles CS arbitration internally.
//
// Calibration constants below were determined empirically for this panel.
// If touch coordinates land consistently off, re-run calibration and update
// these four values. Raw range is typically 200–3800 on each axis.
#define TOUCH_MIN_X   200
#define TOUCH_MAX_X  3800
#define TOUCH_MIN_Y   200
#define TOUCH_MAX_Y  3800

extern TFT_eSPI tft;   // defined in display.cpp

// Last sample, held between reads (touch_hal_read is called every loop).
static uint16_t last_x   = 0;
static uint16_t last_y   = 0;
static bool     last_pressed = false;

void touch_hal_init(void) {
    // TOUCH_IRQ (IO36) is input-only; no pull-up available from the ESP32.
    // We poll via getTouch() rather than using the IRQ pin, which avoids
    // the GPIO36 input-only and no-pullup limitations noted in the review.
    // TFT_eSPI handles the XPT2046 SPI communication automatically.
    pinMode(TOUCH_IRQ, INPUT);
    Serial.println("Touch init OK (XPT2046 via TFT_eSPI)");
}

void touch_hal_read(uint16_t* x, uint16_t* y, bool* pressed) {
    uint16_t tx, ty;
    // getTouch returns true when a touch is detected above the threshold.
    // Threshold 600 filters noise; lower if light touches aren't registering.
    if (tft.getTouch(&tx, &ty, 600)) {
        // Map raw ADC values to display coordinates (landscape 480x320).
        last_x = map(tx, TOUCH_MIN_X, TOUCH_MAX_X, 0, 479);
        last_y = map(ty, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, 319);
        last_x = constrain(last_x, 0, 479);
        last_y = constrain(last_y, 0, 319);
        last_pressed = true;
    } else {
        last_pressed = false;
    }
    *x       = last_x;
    *y       = last_y;
    *pressed = last_pressed;
}