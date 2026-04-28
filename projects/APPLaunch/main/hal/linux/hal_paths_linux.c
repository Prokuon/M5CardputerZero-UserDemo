#include "../hal_paths.h"
#include <stdio.h>
#include <string.h>

static const char *DATA_DIR         = "/usr/share/APPLaunch";
static const char *APPLICATIONS_DIR = "/usr/share/APPLaunch/applications";
static const char *STORE_CACHE_DIR  = "/var/cache/APPLunch/store";
static const char *LOCK_FILE        = "/tmp/M5CardputerZero-APPLaunch_fcntl.lock";
static const char *FONT_DIR         = "/usr/share/APPLaunch/share/font";
static const char *FONT_REGULAR     = "/usr/share/APPLaunch/share/font/AlibabaPuHuiTi-3-55-Regular.ttf";
static const char *FONT_MONO        = "/usr/share/APPLaunch/share/font/LiberationMono-Regular.ttf";
static const char *KBD_DEVICE       = "/dev/input/by-path/platform-3f804000.i2c-event";
static const char *KBD_MAP          = "/usr/share/keymaps/tca8418_keypad_m5stack_keymap.map";
static const char *STORE_SYNC_CMD   = "python /usr/share/APPLaunch/bin/store_cache_sync.py";

void hal_paths_init(const char *exe_dir)
{
    (void)exe_dir;
}

const char *hal_path_data_dir(void)         { return DATA_DIR; }
const char *hal_path_applications_dir(void) { return APPLICATIONS_DIR; }
const char *hal_path_store_cache_dir(void)  { return STORE_CACHE_DIR; }
const char *hal_path_lock_file(void)        { return LOCK_FILE; }
const char *hal_path_font_dir(void)         { return FONT_DIR; }
const char *hal_path_font_regular(void)     { return FONT_REGULAR; }
const char *hal_path_font_mono(void)        { return FONT_MONO; }
const char *hal_path_keyboard_device(void)  { return KBD_DEVICE; }
const char *hal_path_keyboard_map(void)     { return KBD_MAP; }
const char *hal_path_store_sync_cmd(void)   { return STORE_SYNC_CMD; }
