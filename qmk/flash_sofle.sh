set -e
# Setup left
echo "Get sudo password saved"
sudo ls

echo "PUT INTO FLASH MODE"

# Flash left!
sudo make sofle:${1}:avrdude MASTER=right
