set -e

echo "Plug in LEFT"
echo "PUT LEFT SIDE INTO FLASH MODE"

make keebio/iris/rev3:${1}:dfu

echo "Unplug, LEFT, plugin in RIGHT"
echo "PUT RIGHT SIDE INTO FLASH MODE"
sleep 12

make keebio/iris/rev3:${1}:dfu
