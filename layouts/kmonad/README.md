## Building Kmonad
- Uninstall karabiner stuff then restart
  - https://raw.githubusercontent.com/pqrs-org/Karabiner-VirtualHIDDevice/master/dist/uninstall.sh
- Install for M1 following these directions
  - https://github.com/kmonad/kmonad/issues/334#issuecomment-1000106276
- stack make with the dext
  - https://github.com/kmonad/kmonad/blob/master/doc/installation.md#installing-the-kext

```
stack build --flag kmonad:dext --extra-include-dirs=c_src/mac/Karabiner-DriverKit-VirtualHIDDevice/include/pqrs/karabiner/driverkit:c_src/mac/Karabiner-DriverKit-VirtualHIDDevice/src/Client/vendor/include
```
