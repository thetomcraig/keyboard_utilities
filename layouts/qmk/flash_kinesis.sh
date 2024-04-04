#!/bin/bash
rm -rf ${HOME}/qmk_firmware/keyboards/handwired/dactyl_kinesis 
cp -r dactyl_kinesis ${HOME}/qmk_firmware/keyboards/handwired/dactyl_kinesis
cp common_macros.h ${HOME}/qmk_firmware/keyboards/handwired/dactyl_kinesis/common_macros.h
cp secrets.h ${HOME}/qmk_firmware/keyboards/handwired/dactyl_kinesis/secrets.h
cd ${HOME}/qmk_firmware
qmk compile -kb handwired/dactyl_kinesis -km thetomcraig
