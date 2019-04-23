# Generate the new binary (configurator, whatever)

rm -rf ergodox_binary_files
mkdir ergodox_binary_files

unzip "${1}" -d ergodox_binary_files

cd ergodox_binary_files
echo "Put dox in flash mode, then wait 5s"
sleep 5
dfu-util -D right_kiibohd.dfu.bin

cd ..
rm -rf ergodox_binary_files
