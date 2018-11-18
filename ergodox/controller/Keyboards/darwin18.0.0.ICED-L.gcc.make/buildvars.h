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
#define CLI_Revision            "35e1ae6f56f0376a10784d26618d5a8ac3a118ed"
#define CLI_RevisionNumber      31
#define CLI_RevisionNumberStr   "31"
#define CLI_Version             ""
#define CLI_VersionRevision     "35e1ae6f56f0376a10784d26618d5a8ac3a118ed"
#define CLI_VersionRevNumber    31
#define CLI_VersionRevNumberStr "31"
#define CLI_Branch              "master"
#define CLI_ModifiedStatus      "Dirty"
#define CLI_ModifiedFiles       "\r\n\tergodox/brew_packages.txt\r\n\tergodox/controller/.gitignore\r\n\tergodox/controller/98-kiibohd.rules\r\n\tergodox/controller/Bootloader/CMakeLists.txt\r\n\tergodox/controller/Bootloader/Devices/Infinity_Ergodox.c\r\n\tergodox/controller/Bootloader/Devices/K-Type.c\r\n\tergodox/controller/Bootloader/Devices/Kira.c\r\n\tergodox/controller/Bootloader/Devices/WhiteFox.c\r\n\tergodox/controller/Bootloader/Devices/mk20dx128vlf5.c\r\n\tergodox/controller/Bootloader/Devices/mk20dx128vlh7.c\r\n\tergodox/controller/Bootloader/Devices/mk20dx256vlh7.c\r\n\tergodox/controller/Bootloader/Devices/mk22fx512avlh12.c\r\n\tergodox/controller/Bootloader/_buildvars.h\r\n\tergodox/controller/Bootloader/debug.c\r\n\tergodox/controller/Bootloader/debug.h\r\n\tergodox/controller/Bootloader/dfu.c\r\n\tergodox/controller/Bootloader/dfu.desc.c\r\n\tergodox/controller/Bootloader/dfu.desc.h\r\n\tergodox/controller/Bootloader/dfu.h\r\n\tergodox/controller/Bootloader/flash.c\r\n\tergodox/controller/Bootloader/flash.h\r\n\tergodox/controller/Bootloader/kinetis.c\r\n\tergodox/controller/Bootloader/main.c\r\n\tergodox/controller/Bootloader/mchck.h\r\n\tergodox/controller/Bootloader/sim.h\r\n\tergodox/controller/Bootloader/usb.c\r\n\tergodox/controller/Bootloader/usb.h\r\n\tergodox/controller/Bootloader/usbotg.h\r\n\tergodox/controller/Bootloader/weak.h\r\n\tergodox/controller/CMakeLists.txt\r\n\tergodox/controller/Debug/cli/cli.c\r\n\tergodox/controller/Debug/led/led.c\r\n\tergodox/controller/Debug/led/led.h\r\n\tergodox/controller/Dockerfiles/Dockerfile\r\n\tergodox/controller/Dockerfiles/Dockerfile.ubuntu\r\n\tergodox/controller/Dockerfiles/README.md\r\n\tergodox/controller/Dockerfiles/common.bash\r\n\tergodox/controller/Dockerfiles/docker.bash\r\n\tergodox/controller/Lib/CMake/arm.cmake\r\n\tergodox/controller/Lib/CMake/build.cmake\r\n\tergodox/controller/Lib/CMake/dfuMessage\r\n\tergodox/controller/Lib/CMake/host.cmake\r\n\tergodox/controller/Lib/CMake/kll.cmake\r\n\tergodox/controller/Lib/CMake/prependKey\r\n\tergodox/controller/Lib/CMake/sam.cmake\r\n\tergodox/controller/Lib/arm_cortex.c\r\n\tergodox/controller/Lib/chip_version.h\r\n\tergodox/controller/Lib/delay.c\r\n\tergodox/controller/Lib/entropy.c\r\n\tergodox/controller/Lib/kinetis.c\r\n\tergodox/controller/Lib/ld/sam4s16b.ld\r\n\tergodox/controller/Lib/ld/sam4s16c.ld\r\n\tergodox/controller/Lib/ld/sam4s8b.ld\r\n\tergodox/controller/Lib/ld/sam4s8c.ld\r\n\tergodox/controller/Lib/ld/sam4sa16b.ld\r\n\tergodox/controller/Lib/ld/sam4sa16c.ld\r\n\tergodox/controller/Lib/ld/sam4sd16b.ld\r\n\tergodox/controller/Lib/ld/sam4sd16c.ld\r\n\tergodox/controller/Lib/ld/sam4sd32b.ld\r\n\tergodox/controller/Lib/ld/sam4sd32c.ld\r\n\tergodox/controller/Lib/mcu_compat.h\r\n\tergodox/controller/Lib/nrf5.c\r\n\tergodox/controller/Lib/periodic.c\r\n\tergodox/controller/Lib/sam.c\r\n\tergodox/controller/Lib/sam.h\r\n\tergodox/controller/Lib/time.c\r\n\tergodox/controller/LoadFile/load.jlink\r\n\tergodox/controller/Macro/PartialMap/capabilities.kll\r\n\tergodox/controller/Macro/PartialMap/kll.c\r\n\tergodox/controller/Macro/PartialMap/kll.h\r\n\tergodox/controller/Macro/PartialMap/layer.c\r\n\tergodox/controller/Macro/PartialMap/macro.c\r\n\tergodox/controller/Macro/PartialMap/macro.h\r\n\tergodox/controller/Macro/PartialMap/result.c\r\n\tergodox/controller/Macro/PartialMap/trigger.c\r\n\tergodox/controller/Macro/PixelMap/capabilities.kll\r\n\tergodox/controller/Macro/PixelMap/pixel.c\r\n\tergodox/controller/Macro/PixelMap/pixel.h\r\n\tergodox/controller/Output/SeggerRTT/SEGGER_RTT_Conf.h\r\n\tergodox/controller/Output/SeggerRTT/output_rtt.c\r\n\tergodox/controller/Output/SeggerRTT/setup.cmake\r\n\tergodox/controller/Output/USB/arm/usb_desc.c\r\n\tergodox/controller/Output/USB/arm/usb_desc.h\r\n\tergodox/controller/Output/USB/arm/usb_dev.c\r\n\tergodox/controller/Output/USB/arm/usb_dev.h\r\n\tergodox/controller/Output/USB/arm/usb_mem.c\r\n\tergodox/controller/Output/USB/arm/usb_serial.c\r\n\tergodox/controller/Output/USB/output_usb.c\r\n\tergodox/controller/Output/USB/setup.cmake\r\n\tergodox/controller/README.md\r\n\tergodox/controller/Scan/CK3/defaultMap.kll\r\n\tergodox/controller/Scan/CK3/matrix.h\r\n\tergodox/controller/Scan/CK3/scan_loop.c\r\n\tergodox/controller/Scan/CK3/scan_loop.h\r\n\tergodox/controller/Scan/CK3/setup.cmake\r\n\tergodox/controller/Scan/Devices/ISSILed/capabilities.kll\r\n\tergodox/controller/Scan/Devices/ISSILed/i2c.c\r\n\tergodox/controller/Scan/Devices/ISSILed/led_scan.c\r\n\tergodox/controller/Scan/Devices/ISSILed/led_scan.h\r\n\tergodox/controller/Scan/Devices/MatrixARM/capabilities.kll\r\n\tergodox/controller/Scan/Devices/MatrixARM/matrix_scan.c\r\n\tergodox/controller/Scan/Devices/MatrixARM/matrix_scan.h\r\n\tergodox/controller/Scan/Devices/MatrixARM/matrix_setup.h\r\n\tergodox/controller/Scan/Devices/MatrixARM/setup.cmake\r\n\tergodox/controller/Scan/Devices/MatrixARMPeriodic/capabilities.kll\r\n\tergodox/controller/Scan/Devices/MatrixARMPeriodic/matrix_scan.c\r\n\tergodox/controller/Scan/Devices/MatrixARMPeriodic/matrix_scan.h\r\n\tergodox/controller/Scan/Devices/MatrixARMPeriodic/matrix_setup.h\r\n\tergodox/controller/Scan/Devices/MatrixARMPeriodic/setup.cmake\r\n\tergodox/controller/Scan/Devices/PortSwap/capabilities.kll\r\n\tergodox/controller/Scan/Devices/PortSwap/port_scan.c\r\n\tergodox/controller/Scan/Devices/README.md\r\n\tergodox/controller/Scan/ICPad/matrix.h\r\n\tergodox/controller/Scan/Infinity_60/matrix.h\r\n\tergodox/controller/Scan/Infinity_60/scancode_map.kll\r\n\tergodox/controller/Scan/Infinity_60/setup.cmake\r\n\tergodox/controller/Scan/Infinity_60_LED/matrix.h\r\n\tergodox/controller/Scan/Infinity_60_LED/scancode_map.kll\r\n\tergodox/controller/Scan/Infinity_60_LED/setup.cmake\r\n\tergodox/controller/Scan/Infinity_Ergodox/matrix.h\r\n\tergodox/controller/Scan/Infinity_Ergodox/scancode_map.kll\r\n\tergodox/controller/Scan/Infinity_Ergodox/setup.cmake\r\n\tergodox/controller/Scan/K-Type/matrix.h\r\n\tergodox/controller/Scan/K-Type/scancode_map.kll\r\n\tergodox/controller/Scan/K-Type/scancode_map.p2.kll\r\n\tergodox/controller/Scan/K-Type/scancode_map.p3.kll\r\n\tergodox/controller/Scan/K-Type/setup.cmake\r\n\tergodox/controller/Scan/Kira/matrix.h\r\n\tergodox/controller/Scan/Kira/scan_loop.c\r\n\tergodox/controller/Scan/Kira/scancode_map.kll\r\n\tergodox/controller/Scan/Kira/setup.cmake\r\n\tergodox/controller/Scan/MD1\r\n\tergodox/controller/Scan/MD1.1\r\n\tergodox/controller/Scan/MDErgo1\r\n\tergodox/controller/Scan/README.md\r\n\tergodox/controller/Scan/TestIn/Tests/common.py\r\n\tergodox/controller/Scan/TestIn/Tests/kll.py\r\n\tergodox/controller/Scan/TestIn/capabilities.kll\r\n\tergodox/controller/Scan/TestIn/host.py\r\n\tergodox/controller/Scan/TestIn/scan_loop.c\r\n\tergodox/controller/Scan/TestIn/scancode_map.kll\r\n\tergodox/controller/Scan/WhiteFox/matrix.h\r\n\tergodox/controller/Scan/WhiteFox/scancode_map.kll\r\n\tergodox/controller/Scan/WhiteFox/setup.cmake\r\n\tergodox/controller/appveyor.yml\r\n\tergodox/controller/main.c\r\n\tergodox/tom-setup.sh"
#define CLI_RepoOrigin          "git@github.com:thetomcraig/keyboard_utilities.git"
#define CLI_CommitDate          "2018-11-17 19:42:53 -0800"
#define CLI_CommitAuthor        "Tom Craig <thetomcraig@icloud.com>"
#define CLI_Modules             "Scan(Infinity_Ergodox) Macro(PixelMap) Output(USB) Debug(full)"
#define CLI_BuildDate           "2018-11-17 19:49:07 -0800"
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
#define BCD_VERSION             31

