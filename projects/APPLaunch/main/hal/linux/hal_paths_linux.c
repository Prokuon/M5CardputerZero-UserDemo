#include "../hal_paths.h"
#include <stdio.h>
#include <string.h>

static char s_data_dir[512]         = ".";
static char s_applications_dir[512] = "/usr/share/APPLaunch/applications";
static char s_store_cache_dir[512]  = "/var/cache/APPLaunch/store";
static char s_lock_file[512]        = "/tmp/M5CardputerZero-APPLaunch_fcntl.lock";
static char s_font_dir[512]         = "./images";
static char s_font_regular[512]     = "./images/AlibabaPuHuiTi-3-55-Regular.ttf";
static char s_font_mono[512]        = "./images/LiberationMono-Regular.ttf";
static char s_images_dir[512]       = "./images";
static const char *KBD_DEVICE       = "/dev/input/by-path/platform-3f804000.i2c-event";
static const char *KBD_MAP          = "/usr/share/keymaps/tca8418_keypad_m5stack_keymap.map";
static char s_store_sync_cmd[512]   = "python dist/store_cache_sync.py";

void hal_paths_init(const char *exe_dir)
{
    if (!exe_dir) exe_dir = ".";
    snprintf(s_data_dir,         sizeof(s_data_dir),         "%s", exe_dir);
    snprintf(s_images_dir,       sizeof(s_images_dir),       "%s/images", exe_dir);
    snprintf(s_font_dir,         sizeof(s_font_dir),         "%s/images", exe_dir);
    snprintf(s_font_regular,     sizeof(s_font_regular),     "%s/images/AlibabaPuHuiTi-3-55-Regular.ttf", exe_dir);
    snprintf(s_font_mono,        sizeof(s_font_mono),        "%s/images/LiberationMono-Regular.ttf", exe_dir);
    snprintf(s_store_sync_cmd,   sizeof(s_store_sync_cmd),   "python %s/store_cache_sync.py", exe_dir);
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
