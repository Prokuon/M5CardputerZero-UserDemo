#pragma once

/*
 * Exactly one of these is defined by CMake:
 *   HAL_PLATFORM_LINUX  -- native Raspberry Pi CM Zero
 *   HAL_PLATFORM_SDL    -- macOS / Linux desktop emulator (SDL2)
 *   HAL_PLATFORM_WIN32  -- Windows MinGW + SDL2
 *   HAL_PLATFORM_WEB    -- Emscripten + SDL2
 */

#if !defined(HAL_PLATFORM_LINUX) && !defined(HAL_PLATFORM_SDL) && \
    !defined(HAL_PLATFORM_WIN32) && !defined(HAL_PLATFORM_WEB)
#error "No HAL platform defined. Set -DHAL_PLATFORM_xxx=1 in CMake."
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
