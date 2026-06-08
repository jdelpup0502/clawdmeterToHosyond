#include "../../hal/display_hal.h"
#include "board.h"
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

// TFT_eSPI is configured entirely via build_flags in platformio.ini —
// no User_Setup.h edits needed. The flags mirror the factory User_Setup.h
// that was confirmed working on this board (core 2.0.x, 80 MHz, VSPI).

TFT_eSPI tft;   // non-static: accessible from touch.cpp via extern

void display_hal_init(void) {
    tft.init();
    tft.setRotation(1);
    tft.setSwapBytes(true);
}

void display_hal_begin(void) {
    tft.fillScreen(TFT_BLACK);
    digitalWrite(LCD_BL, HIGH);   // backlight on after panel is cleared
}

void display_hal_set_brightness(uint8_t level) {
    // This board has no PWM brightness control — backlight is on/off only.
    // Map 0 → off, anything else → on. The shared code uses 0/255 endpoints
    // for the rotation-transition blank/restore, so this is sufficient.
    digitalWrite(LCD_BL, level > 0 ? HIGH : LOW);
}

void display_hal_fill_screen(uint16_t color565) {
    tft.fillScreen(color565);
}

// LVGL flush callback target. Shared main.cpp calls this with each partial
// render strip. TFT_eSPI's pushImage pushes the RGB565 buffer to the panel.
void display_hal_draw_bitmap(int32_t x, int32_t y, int32_t w, int32_t h,
                             const uint16_t* pixels) {
    static int count = 0;
    if (count < 3) { Serial.printf("draw_bitmap #%d: %d,%d %dx%d\n", count++, x, y, w, h); }
    tft.pushImage(x, y, w, h, (uint16_t*)pixels);
}

// No-op: this board has no IMU and doesn't need per-loop display housekeeping.
void display_hal_tick(void) {}

// No alignment requirement for ST7796 over SPI — pass through unchanged.
void display_hal_round_area(int32_t* x1, int32_t* y1,
                            int32_t* x2, int32_t* y2) {
    (void)x1; (void)y1; (void)x2; (void)y2;
}