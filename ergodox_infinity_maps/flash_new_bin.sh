# Generate the new binary (configurator, whatever)
echo "Put dox in flash mode, then wait 5s"
sleep 5
dfu-util -D "${1}" 
