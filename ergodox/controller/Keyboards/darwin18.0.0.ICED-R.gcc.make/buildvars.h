/* Copyright (C) 2013-2017 by Jacob Alexander
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

// ----- Includes -----



// ----- Defines -----

// Helpers
#define _STR_HELPER(x)
#define _STR(x) _STR_HELPER(x)

// You can change these to give your code its own name.
#define STR_MANUFACTURER        L"Input Club"
#define STR_PRODUCT             L"Keyboard - Infinity_Ergodox PixelMap USB"
#define STR_SERIAL              L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX - mk20dx256"
#define STR_CONFIG_NAME         L"xXXx"


// Strings used in the CLI module
#define CLI_Revision            "5c882b882a6f9e95c08dc1cc0287a194bf58d045"
#define CLI_RevisionNumber      32
#define CLI_RevisionNumberStr   "32"
#define CLI_Version             ""
#define CLI_VersionRevision     "5c882b882a6f9e95c08dc1cc0287a194bf58d045"
#define CLI_VersionRevNumber    32
#define CLI_VersionRevNumberStr "32"
#define CLI_Branch              "master"
#define CLI_ModifiedStatus      "Dirty"
#define CLI_ModifiedFiles       "\r\n\t.gitignore\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeCache.txt\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/CMakeDirectoryInformation.cmake\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/CMakeRuleHashes.txt\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/DFUMessage.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/Makefile2\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/SizeAfter.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/TargetDirectories.txt\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/C.includecache\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Debug/cli/cli.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Debug/latency/latency.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Debug/led/led.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Debug/print/print.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/DependInfo.cmake\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Lib/arm_cortex.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Lib/delay.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Lib/entropy.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Lib/gpio.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Lib/kinetis.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Lib/periodic.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Lib/storage.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Lib/time.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Macro/PartialMap/kll.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Macro/PartialMap/layer.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Macro/PartialMap/macro.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Macro/PartialMap/result.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Macro/PartialMap/trigger.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Macro/PixelMap/pixel.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/HID-IO/hidio_com.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/Interface/output_gen.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/arm/usb_desc.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/arm/usb_dev.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/arm/usb_joystick.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/arm/usb_keyboard.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/arm/usb_mem.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/arm/usb_mouse.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/arm/usb_rawio.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/arm/usb_serial.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/output_com.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Output/USB/output_usb.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Scan/Devices/ISSILed/i2c.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Scan/Devices/ISSILed/led_scan.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Scan/Devices/MatrixARMPeriodic/matrix_scan.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Scan/Devices/STLcd/lcd_scan.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Scan/Devices/UARTConnect/connect_scan.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/Scan/Infinity_Ergodox/scan_loop.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/depend.internal\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/flags.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/generatedPixelmap.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/link.txt\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kiibohd.dir/main.c.obj\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kll_debug.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kll_display.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kll_final_display.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kll_parser.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kll_regen.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/CMakeFiles/kll_token.dir/build.make\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/Makefile\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/buildvars.h\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/cmake_install.cmake\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/compile_commands.json\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/generatedKeymap.h\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/generatedPixelmap.c\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/kiibohd.dfu.bin\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/kiibohd.elf\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/kiibohd.lss\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/kiibohd.secure.dfu.bin\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/kiibohd.sym\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/kll_defs.h\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/link.map\r\n\tergodox/controller/Keyboards/darwin18.0.0.ICED-L.gcc.make/usb_hid.h\r\n\tergodox/controller/compile_commands.json\r\n\tergodox/controller/tags"
#define CLI_RepoOrigin          "git@github.com:thetomcraig/keyboard_utilities.git"
#define CLI_CommitDate          "2018-11-17 19:50:46 -0800"
#define CLI_CommitAuthor        "Tom Craig <thetomcraig@icloud.com>"
#define CLI_Modules             "Scan(Infinity_Ergodox) Macro(PixelMap) Output(USB) Debug(full)"
#define CLI_BuildDate           "2018-11-30 15:21:11 -0800"
#define CLI_BuildOS             "Generic"
#define CLI_BuildCompiler       "/usr/local/bin/arm-none-eabi-gcc 7.3.1"
#define CLI_Arch                "arm"
#define CLI_Chip                "mk20dx256vlh7"
#define CLI_ChipShort           "mk20dx256"
#define CLI_CPU                 "cortex-m4"
#define CLI_Device              "Keyboard"


// Mac OS-X and Linux automatically load the correct drivers.  On
// Windows, even though the driver is supplied by Microsoft, an
// INF file is needed to load the driver.  These numbers need to
// match the INF file.
#define VENDOR_ID               0x308F
#define PRODUCT_ID              0x0004
#define BCD_VERSION             32

