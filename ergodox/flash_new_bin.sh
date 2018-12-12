# Generate the new binary (configurator, whatever)
# Place binary here and rename it "ergodox_binary.zip"

unzip ergodox_binary.zip ergodox_binary_files
cd ergodox_binary_files
echo "Put dox in flash mode, then wait 5s"
sleep 5
dfu dfu-util -D right_kiibohd.dfu.bin
