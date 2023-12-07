/*
Copyright 2017 Fred Sundvik

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "simple_visualizer.h"
#include "util.h"

// Copied from keymap.c
enum ergodox_layers {
    DOX_BASE,
    DOX_LYR1,
    DOX_LYR2,
};

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 255;

    uint8_t layer = biton32(state->status.layer);
    state->target_lcd_color = LCD_COLOR(layer << 2, saturation, 0xFF);

    switch(layer) {
        case DOX_BASE:
            state->layer_text = "BASE";
            break;
        case DOX_LYR1:
            state->layer_text = "MEDIA";
            break;
        case DOX_LYR2:
            state->layer_text = "WINDOWS";
            break;
        default:
            state->layer_text = "NONE";
            break;
    }
}
