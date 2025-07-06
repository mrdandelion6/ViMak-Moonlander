# ViMak Moonlander
This is a keyboard layout for using Colemak-DH and Neovim on the ZSA Moolander. Here is the config I use for Neovim: [six.nvim](https://github.com/mrdandelion6/six.nvim)

## Setting up QMK Software
### Set up QMK Environment
Use the documentation at [https://docs.qmk.fm/](https://docs.qmk.fm/#/newbs_getting_started?id=set-up-your-environment) to set up your environment for building your firmware. Don't run `qmk setup`.

### Get ZSA's QMK Firmware
You need to build your layout against [https://github.com/zsa/qmk_firmware/](https://github.com/zsa/qmk_firmware/) which is ZSA's QMK fork (instead of qmk/qmk_firmware). This is what Oryx (ZSA's graphical configurator) uses, so it's guaranteed to work. A common place is just `~/qmk_firmware/`. Run the command below:
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

## Debugging
If you want to debug the layout with print statements , you will need to set `CONSOLE_ENABLE=true` in `rules.mk`. Then you can use `hid_listen` in terminal and any time your print statements are trigerred , it will print them. Note , you will need to use `uprintf` instead of `printf`.

`hid_listen` comes installed with `qmk` CLI on Ubuntu , but on Arch you need to install `hid_listen`:
```bash
# on arch
yay -S hid_listen
```

## TODO
Here is a TODO for layers and RGB.

### RGB
- CMK: pink purple wave
- QTY: red orange wave
- SYM: purple pink red orange wave
- NUM: pink red wave
- VIM: blue purple wave
- APP: teal blue wave

### CMK

### NUM
- add alt f4 shortcut on left side

### VIM
Set the following vim binds:
- y, Y, yy
- p, pp
- w, b, j
- gg, G
- ctrl d, ctrl u
