#include "../hal_paths.h"
#include <stdio.h>
#include <string.h>

#define APP_PREFIX "/usr/share/APPLaunch"

static char s_data_dir[512]         = APP_PREFIX;
static char s_applications_dir[512] = APP_PREFIX "/applications";
static char s_store_cache_dir[512]  = "/var/cache/APPLaunch/store";
static char s_lock_file[512]        = "/tmp/M5CardputerZero-APPLaunch_fcntl.lock";
static char s_font_dir[512]         = APP_PREFIX "/share/images";
static char s_font_regular[512]     = APP_PREFIX "/share/images/AlibabaPuHuiTi-3-55-Regular.ttf";
static char s_font_mono[512]        = APP_PREFIX "/share/images/LiberationMono-Regular.ttf";
static char s_images_dir[512]       = APP_PREFIX "/share/images";
static const char *KBD_DEVICE       = "/dev/input/by-path/platform-3f804000.i2c-event";
static const char *KBD_MAP          = "/usr/share/keymaps/tca8418_keypad_m5stack_keymap.map";
static char s_store_sync_cmd[512]   = "python " APP_PREFIX "/bin/store_cache_sync.py";

void hal_paths_init(const char *exe_dir)
{
    const char *base = exe_dir ? exe_dir : APP_PREFIX;
    snprintf(s_data_dir,         sizeof(s_data_dir),         "%s", base);
    snprintf(s_images_dir,       sizeof(s_images_dir),       "%s/share/images", base);
    snprintf(s_font_dir,         sizeof(s_font_dir),         "%s/share/images", base);
    snprintf(s_font_regular,     sizeof(s_font_regular),     "%s/share/images/AlibabaPuHuiTi-3-55-Regular.ttf", base);
    snprintf(s_font_mono,        sizeof(s_font_mono),        "%s/share/images/LiberationMono-Regular.ttf", base);
    snprintf(s_store_sync_cmd,   sizeof(s_store_sync_cmd),   "python %s/bin/store_cache_sync.py", base);
}

const char *hal_path_data_dir(void)         { return s_data_dir; }
const char *hal_path_applications_dir(void) { return s_applications_dir; }
const char *hal_path_store_cache_dir(void)  { return s_store_cache_dir; }
const char *hal_path_lock_file(void)        { return s_lock_file; }
const char *hal_path_font_dir(void)         { return s_font_dir; }
const char *hal_path_font_regular(void)     { return s_font_regular; }
const char *hal_path_font_mono(void)        { return s_font_mono; }
const char *hal_path_keyboard_device(void)  { return KBD_DEVICE; }
const char *hal_path_keyboard_map(void)     { return KBD_MAP; }
const char *hal_path_store_sync_cmd(void)   { return s_store_sync_cmd; }
const char *hal_path_images_dir(void)       { return s_images_dir; }
