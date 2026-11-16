# vimak moonlander

this is a keyboard layout for using colemak-dh and neovim on the zsa moolander. here is the config i use for neovim: [six.nvim](https://github.com/mrdandelion6/six.nvim)

## setting up qmk software

### set up qmk environment

use the documentation at [https://docs.qmk.fm/](https://docs.qmk.fm/#/newbs_getting_started?id=set-up-your-environment) to set up your environment for building your firmware. don't run `qmk setup`.

afterwards , clone this repository anywhere you want.

### get zsa's qmk firmware

you need to build your layout against [https://github.com/zsa/qmk_firmware/](https://github.com/zsa/qmk_firmware/) which is zsa's qmk fork (instead of qmk/qmk_firmware). this is what oryx (zsa's graphical configurator) uses, so it's guaranteed to work. run the following command to set qmk to point to zsa's firmware:

```bash
# choose a place to clone , e.g. ~/qmk_firmware
qmk setup zsa/qmk_firmware -b firmware24 -H ~/qmk_firmware
```

the above command both retrieve's zsa's firmware from git and tells qmk where it is. now you're all done with setting up the software.

## setting up this repo

make a file named `qmk_path.txt` in the root of this repo and edit it to have the actual path pointing to zsa's `qmk_firmware/` repo (wherever you cloned it).

```bash
# change to the path where you cloned
echo "~/qmk_firmware/" > qmk_path.txt
```

## compiling

simply run `make` from the `src/` directory after finishing set up. if you have any dependency issues , follow the instructions from the error messages and fix it. the binary will be generated and move to the `build/` dir.

## flashing

now flash to your keyboard , first attempt to flash the binary:

```bash
# from src/
qmk flash ../build/zsa_moonlander_vimak.bin
```

qmk will say "Please reset your keyboard into bootloader mode now!" , this is when you need to put the keyboard in bootloader mode. to put your keyboard in bootloader mode press the reset button on your clipboard. it might be in the top left of the left half , and you will likely need a paper clip.

after the keyboard is in bootloader mode , it will let qmk flash it automatically. after flashing , the keyboard should restart on its won and be ready for use.

## debugging

if you want to debug the layout with print statements , you will need to set `CONSOLE_ENABLE=true` in `rules.mk`. then you can use `hid_listen` in terminal and any time your print statements are trigerred , it will print them. note , you will need to use `uprintf` instead of `printf`.

`hid_listen` comes installed with `qmk` cli on ubuntu , but on arch you need to install `hid_listen`:

```bash
# on arch
yay -S hid_listen
```

if you want to just what keys are being pressed before your desktop intercepts them , you can do so with `evtest`.

```sh
pacman -S evtest
```

## fast key presses

on the moonlander , tap SYM for symbols and hold it for app shortcuts. `T` is terminal in APP and `{` in SYM. the key released first decides , not speed (qmk permissive hold):

```
SYM↓ T↓ T↑ SYM↑   ->  terminal
SYM↓ T↓ SYM↑ T↑   ->  {
```

making any key pressed during SYM count as a hold would be worse , since fast typing overlaps keys a lot and would keep opening terminals.

## todo

here is a todo for layers and rgb.

### rgb

- CMK: pink purple wave
- QTY: red orange wave
- SYM: purple pink red orange wave
- NUM: pink red wave
- VIM: blue purple wave
- APP: teal blue wave

### vim

set the following vim binds:

- y, Y, yy
- p, pp
- w, b, j
- gg, G
- ctrl d, ctrl u
