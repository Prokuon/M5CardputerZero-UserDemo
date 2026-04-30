/*
 * ui_global_hint.cpp
 *
 * Transient on-screen hint/toast overlay.
 *
 * Behavior:
 *   (a) Single press of ESC (key-down, state==1) -> show
 *       "长按 ESC 5秒可返回首页" for ~1.5s.
 *   (b) Single press of SHIFT (Aa / KEY_LEFTSHIFT) or SYM (physical
 *       "SYM" key on the M5 CardputerZero; currently best-effort mapped)
 *       -> show "快速双击可锁定" for ~1.5s.
 *
 *   Fn key is intentionally NOT hinted (no lock feature yet).
 *
 * The toast object is created lazily on first call as a child of
 * lv_layer_top(), so it floats above any screen. It is never deleted
 * (to avoid delete-inside-event issues); visibility is toggled via
 * LV_OBJ_FLAG_HIDDEN. A single lv_timer performs the auto-hide; each
 * new trigger resets the timer's remaining time.
 */

#include "ui_global_hint.h"
#include "ui.h"
#include "keyboard_input.h"
#include "lvgl/lvgl.h"

#include "compat/input_keys.h"

#include <string.h>

/* KEY_RIGHTSHIFT / KEY_COMPOSE exist in <linux/input.h> but the
 * project's non-Linux compat/input_keys.h does not define them.
 * Provide reasonable fallbacks so the file builds on Darwin / SDL too. */
#ifndef KEY_RIGHTSHIFT
#define KEY_RIGHTSHIFT 54
#endif

/* Standard Linux evdev code for the Fn key. Defined here to avoid
 * relying on any particular <linux/input-event-codes.h> having it. */
#ifndef KEY_FN
#define KEY_FN 0x1d0
#endif

/* Fallback: KEY_COMPOSE is the most common evdev code for a physical
 * "SYM" / "Menu" style key; include it alongside LEFTSHIFT / RIGHTSHIFT
 * so the hint fires regardless of which exact code the TCA8418 driver
 * chose for the SYM key on this board. */
#ifndef KEY_COMPOSE
#define KEY_COMPOSE 127
#endif

#define HINT_SHOW_MS        1500
#define HINT_BG_COLOR       0x1F3A5F
#define HINT_BG_OPA         LV_OPA_80
#define HINT_TEXT_COLOR     0xFFFFFF
#define HINT_WIDTH          280
#define HINT_HEIGHT         22
#define HINT_Y_OFFSET       4    /* px below top of screen */

static lv_obj_t  *s_hint_obj   = NULL;
static lv_obj_t  *s_hint_label = NULL;
static lv_timer_t *s_hint_timer = NULL;

static void hint_timer_cb(lv_timer_t *t)
{
    /* One-shot: hide the toast and pause the timer. We keep the timer
     * alive (never let its repeat_count hit zero + auto-delete) so
     * subsequent triggers can just reset it without worrying about
     * dangling pointers. */
    if (s_hint_obj) {
        lv_obj_add_flag(s_hint_obj, LV_OBJ_FLAG_HIDDEN);
    }
    if (t) lv_timer_pause(t);
}

static void ensure_hint_created(void)
{
    if (s_hint_obj != NULL) return;

    lv_obj_t *parent = lv_layer_top();
    if (parent == NULL) return;

    s_hint_obj = lv_obj_create(parent);
    lv_obj_remove_style_all(s_hint_obj);
    lv_obj_set_size(s_hint_obj, HINT_WIDTH, HINT_HEIGHT);
    lv_obj_align(s_hint_obj, LV_ALIGN_TOP_MID, 0, HINT_Y_OFFSET);

    lv_obj_set_style_bg_color(s_hint_obj, lv_color_hex(HINT_BG_COLOR), 0);
    lv_obj_set_style_bg_opa(s_hint_obj, HINT_BG_OPA, 0);
    lv_obj_set_style_radius(s_hint_obj, 6, 0);
    lv_obj_set_style_border_width(s_hint_obj, 0, 0);
    lv_obj_set_style_pad_all(s_hint_obj, 0, 0);
    lv_obj_set_style_shadow_width(s_hint_obj, 0, 0);

    /* Block user interaction — this is purely visual. */
    lv_obj_clear_flag(s_hint_obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(s_hint_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(s_hint_obj, LV_OBJ_FLAG_IGNORE_LAYOUT);

    s_hint_label = lv_label_create(s_hint_obj);
    lv_obj_set_style_text_color(s_hint_label, lv_color_hex(HINT_TEXT_COLOR), 0);
    /* Prefer the project's Chinese-capable 12pt font; it already falls
     * back to lv_font_montserrat_12 inside ui.c if freetype init failed. */
    lv_font_t *font = g_font_cn_12 ? g_font_cn_12
                                   : (lv_font_t *)&lv_font_montserrat_12;
    lv_obj_set_style_text_font(s_hint_label, font, 0);
    lv_label_set_text(s_hint_label, "");
    lv_obj_center(s_hint_label);

    lv_obj_add_flag(s_hint_obj, LV_OBJ_FLAG_HIDDEN);
}

static void show_hint(const char *text)
{
    ensure_hint_created();
    if (s_hint_obj == NULL || s_hint_label == NULL) return;

    lv_label_set_text(s_hint_label, text);
    lv_obj_align(s_hint_obj, LV_ALIGN_TOP_MID, 0, HINT_Y_OFFSET);
    lv_obj_clear_flag(s_hint_obj, LV_OBJ_FLAG_HIDDEN);

    if (s_hint_timer == NULL) {
        s_hint_timer = lv_timer_create(hint_timer_cb, HINT_SHOW_MS, NULL);
    }
    /* Keep the timer alive indefinitely; the callback pauses it after
     * one firing. Resetting here restarts the countdown from zero, so
     * successive hints extend the visible window each time. */
    if (s_hint_timer) {
        lv_timer_set_period(s_hint_timer, HINT_SHOW_MS);
        lv_timer_reset(s_hint_timer);
        lv_timer_resume(s_hint_timer);
    }
}

extern "C" void ui_global_hint_on_key(const struct key_item *elm)
{
    if (elm == NULL) return;

    /* Only fire on the initial key-down edge — not repeats, not releases. */
    if (elm->key_state != KBD_KEY_PRESSED) return;

    const uint32_t code = elm->key_code;

    /* Explicitly skip Fn — no lock feature attached to it. */
    if (code == KEY_FN) return;

    switch (code) {
        case KEY_ESC:
            show_hint("长按 ESC 5秒可返回首页");
            return;

        case KEY_LEFTSHIFT:
        case KEY_RIGHTSHIFT:
        case KEY_COMPOSE:
            show_hint("快速双击可锁定");
            return;

        default:
            break;
    }

    /* Secondary best-effort match for the SYM key: some TCA8418 keymaps
     * tag it with sym_name "Multi_key" / "Menu" / "Sym". Match by name
     * too so we don't miss it if the raw code differs from our fallbacks. */
    if (elm->sym_name[0]) {
        if (strcmp(elm->sym_name, "Multi_key") == 0 ||
            strcmp(elm->sym_name, "Menu")      == 0 ||
            strcmp(elm->sym_name, "Sym")       == 0 ||
            strcmp(elm->sym_name, "SYM")       == 0) {
            show_hint("快速双击可锁定");
        }
    }
}
