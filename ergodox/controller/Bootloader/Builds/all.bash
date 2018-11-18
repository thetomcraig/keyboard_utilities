#!/usr/bin/env bash
# This script runs each of the bootloader build scripts
# Jacob Alexander 2017-2018



########################
# Bash Library Include #
########################

# Shouldn't need to touch this section

# Check if the library can be found
if [ ! -f common.bash ]; then
	echo "ERROR: Cannot find 'common.bash'"
	exit 1
fi

# Load common functions
source "common.bash"



###########
# Scripts #
###########

# Run builds
cmd_cpy ./mk20dx128vlf5.bash   kiibohd_bootloader.bin bootloader/mk20dx128vlf5.bootloader.bin
cmd_cpy ./mk20dx128vlh7.bash   kiibohd_bootloader.bin bootloader/mk20dx128vlh7.bootloader.bin
cmd_cpy ./mk20dx256vlh7.bash   kiibohd_bootloader.bin bootloader/mk20dx256vlh7.bootloader.bin
cmd_cpy ./mk22fx512avlh12.bash kiibohd_bootloader.bin bootloader/mk22fx512avlh12.bootloader.bin
cmd_cpy ./sam4s8b.bash         kiibohd_bootloader.bin bootloader/sam4s8b.bootloader.bin
cmd_cpy ./sam4s8c.bash         kiibohd_bootloader.bin bootloader/sam4s8c.bootloader.bin
cmd_cpy ./ergodox.bash         kiibohd_bootloader.bin bootloader/ergodox.bootloader.bin
cmd_cpy ./geminiduskdawn.bash  kiibohd_bootloader.bin bootloader/geminiduskdawn.bootloader.bin
cmd_cpy ./infinity.bash        kiibohd_bootloader.bin bootloader/infinity.bootloader.bin
cmd_cpy ./infinity_led.bash    kiibohd_bootloader.bin bootloader/infinity_led.bootloader.bin
cmd_cpy ./kira.bash            kiibohd_bootloader.bin bootloader/kira.bootloader.bin
cmd_cpy ./ktype.bash           kiibohd_bootloader.bin bootloader/ktype.bootloader.bin
cmd_cpy ./whitefox.bash        kiibohd_bootloader.bin bootloader/whitefox.bootloader.bin
cmd_cpy ./whitefox_sam4s.bash  kiibohd_bootloader.bin bootloader/whitefox_sam4s.bootloader.bin

# Tally results
result
exit $?

