#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int  hal_keyboard_init(void);
void hal_keyboard_deinit(void);

struct _lv_indev_t *hal_keyboard_get_indev(void);

extern volatile int      HAL_HOME_KEY_FLAG;
extern volatile int      HAL_LVGL_RUN_FLAG;
extern volatile uint32_t HAL_LV_EVENT_KEYBOARD;

#ifdef __cplusplus
}
#endif
