#! /bin/bash

echo "Plug in LEFT, and put into flash mode."
read -p "Done?"
qmk flash -kb input_club/ergodox_infinity -km thetomcraig

echo "Plug in RIGHT, and put into flash mode."
read -p "Done?"
qmk flash -kb input_club/ergodox_infinity -km thetomcraig

