# ViMak Moonlander
This is a keyboard layout for using Colemak-DH and Neovim on the ZSA Moolander.

## Setting up QMK Software
### Set up QMK Environment
Use the documentation at [https://docs.qmk.fm/](https://docs.qmk.fm/#/newbs_getting_started?id=set-up-your-environment) to set up your environment for building your firmware. Don't run `qmk setup`.

### Get ZSA's QMK Firmware
You need to build your layout against [https://github.com/zsa/qmk_firmware/](https://github.com/zsa/qmk_firmware/) which is ZSA's QMK fork (instead of qmk/qmk_firmware). This is what Oryx (ZSA's graphical configurator) uses, so it's guaranteed to work. Simply clone it where you want. A common place is just `~/qmk_firmware/`
```bash
# choose a place to clone , e.g. ~/qmk_firmware
qmk setup zsa/qmk_firmware -b firmware24 -H ~/qmk_firmware
```
This both retrieve's ZSA's firmware from git and tells QMK where it is. Now you're all done with setting up the software.

## Setting up this Repo
Make a file named `qmk_path.txt` and edit it to have the actual path pointing to ZSA's `qmk_firmware/` repo (wherever you cloned it).
```bash
# change to the path where you cloned
echo "~/qmk_firmware/" > qmk_path.txt
```

## Compiling
Simply run `make` from the `src/` directory after finishing set up. If you have any dependency issues , follow the instructions from the error messages and fix it. The binary will be generated and move to the `build/` dir.

## Flashing
Now flash to your keyboard , first attempt to flash the binary:
```bash
# from src/
qmk flash ../build/zsa_moonlander_vimak.bin
```
QMK will say "Please reset your keyboard into bootloader mode now!" , this is when you need to put the keyboard in bootloader mode. To put your keyboard in bootloader mode press the reset button on your clipboard. It might be in the top left of the left half , and you will likely need a paper clip.

After the keyboard is in bootloader mode , it will let QMK flash it automatically. After flashing , the keyboard should restart on its won and be ready for use.
