#!/bin/bash

# should be ran from where this script is located.
# this script ensures you have the keymap and needed parent directories set up in qmk.
# expects an optional argument for where qmk_firmware directory is located.

qmk_dir="$HOME/qmk_firmware/"
if [ -n "$1" ]; then
  qmk_dir="$1"
fi
qmk_dir="${qmk_dir%/}/" # remove duplicated slashes

vimak_dir="${qmk_dir}keyboards/zsa/moonlander/keymaps/vimak/"
mkdir -p "$vimak_dir"

ln -s "$(pwd)/src/keymap.c" "${vimak_dir}keymap.c"
ln -s "$(pwd)/src/config.h" "${vimak_dir}config.h"
ln -s "$(pwd)/src/rules.mk" "${vimak_dir}rules.mk"
