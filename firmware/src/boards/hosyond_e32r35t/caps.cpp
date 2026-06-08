#include "../../hal/board_caps.h"
#include "board.h"

// Landscape: panel is 320x480 in portrait, rotated 90° so effective
// width = 480, height = 320. The LVGL display is created at these dimensions.
static const BoardCaps caps = {
    .name         = BOARD_NAME,
    .width        = LCD_WIDTH,   // 480 in landscape
    .height       = LCD_HEIGHT,  // 320 in landscape
    .button_count = 1,           // BOOT button only
    .has_rotation = false,       // no IMU, fixed landscape
    .has_battery  = false,       // no AXP2101
    .has_imu      = false,
};

const BoardCaps& board_caps(void) { return caps; }
