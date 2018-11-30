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
#define STR_PRODUCT             L"Keyboard - Infinity_60:alphabet PartialMap USB"
#define STR_SERIAL              L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX - mk20dx128"
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
#define CLI_ModifiedStatus      "Clean"
#define CLI_ModifiedFiles       "\r\n\t"
#define CLI_RepoOrigin          "git@github.com:thetomcraig/keyboard_utilities.git"
#define CLI_CommitDate          "2018-11-17 19:50:46 -0800"
#define CLI_CommitAuthor        "Tom Craig <thetomcraig@icloud.com>"
#define CLI_Modules             "Scan(Infinity_60:alphabet) Macro(PartialMap) Output(USB) Debug(full)"
#define CLI_BuildDate           "2018-11-17 19:59:39 -0800"
#define CLI_BuildOS             "Generic"
#define CLI_BuildCompiler       "/usr/local/bin/arm-none-eabi-gcc 7.3.1"
#define CLI_Arch                "arm"
#define CLI_Chip                "mk20dx128vlf5"
#define CLI_ChipShort           "mk20dx128"
#define CLI_CPU                 "cortex-m4"
#define CLI_Device              "Keyboard"


// Mac OS-X and Linux automatically load the correct drivers.  On
// Windows, even though the driver is supplied by Microsoft, an
// INF file is needed to load the driver.  These numbers need to
// match the INF file.
#define VENDOR_ID               0x308F
#define PRODUCT_ID              0xB04D
#define BCD_VERSION             32

