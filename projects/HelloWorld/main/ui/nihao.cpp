#include "lvgl/lvgl.h"

void ui_init()
{
    lv_obj_t *screen = lv_screen_active();

    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, "Hello World!");
    lv_obj_center(label);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);

    lv_obj_set_style_bg_color(screen, lv_color_hex(0x1A1A2E), 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
}
