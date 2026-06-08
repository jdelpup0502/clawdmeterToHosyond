#pragma once

// Hosyond 3.5" ESP32-32E Display (E32R35T)
// ST7796U, 320x480 resistive touch (XPT2046), shared SPI bus, no PSRAM.
// Pins confirmed from manufacturer wiki (lcdwiki E32R35T pin assignment).
// Core: ESP32 Arduino 2.0.x — required for TFT_eSPI SPI compatibility.

#define BOARD_NAME  "Hosyond E32R35T"

// ---- Display geometry ----
#define LCD_WIDTH   480   // landscape (rotation=1): physical 320 becomes height
#define LCD_HEIGHT  320

// ---- SPI display pins (ST7796, 4-wire SPI, VSPI default) ----
#define LCD_MISO    12
#define LCD_MOSI    13
#define LCD_SCLK    14
#define LCD_CS      15
#define LCD_DC       2
#define LCD_RST     -1    // tied to board EN — no dedicated GPIO
#define LCD_BL      27    // backlight, active HIGH

// ---- Touch (XPT2046, shares the SPI bus above) ----
#define TOUCH_CS    33
#define TOUCH_IRQ   36    // input-only pin, active LOW on touch

// ---- RGB status LED (common anode: LOW = on, HIGH = off) ----
#define LED_R       22
#define LED_G       16
#define LED_B       17

// ---- BOOT button (GPIO 0, active LOW) — primary input ----
#define BTN_BOOT     0

// ---- Capability flags ----
// No secondary hardware button (no AXP2101, no side buttons).
// No IMU, no PSRAM, no battery management IC.
#define BOARD_HAS_SECONDARY_BUTTON  0
#define BOARD_HAS_ROTATION          0
#define BOARD_HAS_IMU               0
#define BOARD_HAS_BATTERY           0
#define BOARD_HAS_IO_EXPANDER       0
