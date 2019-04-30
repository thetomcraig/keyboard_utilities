# Setup left
echo "Get sudo password saved"
sudo ls
echo "Make left side"
make ergodox_infinity:${1}

# Flash left!
echo "Unplug, then plug in ONLY left"
sleep 5
echo "Put left side into flash mode"
sleep 2
sudo make ergodox_infinity:${1}:dfu-util

# Setup left
echo "Make right side"
make ergodox_infinity:${1} MASTER=right

# Flash right!
echo "Unplug, then plug in ONLY right"
sleep 5
echo "Put right side into flash mode"
sleep 2
sudo make ergodox_infinity:${1}:dfu-util MASTER=right
