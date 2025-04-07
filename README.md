# ViMak Moonlander
This is a keyboard layout for using Colemak-DH and Neovim on the ZSA Moolander.

## Setting Up QMK
- Use the documentation at [https://docs.qmk.fm/](https://docs.qmk.fm/) to set up your environment for building your firmware.
- Build your layout against [https://github.com/zsa/qmk_firmware/](https://github.com/zsa/qmk_firmware/) which is ZSA's QMK fork (instead of qmk/qmk_firmware). This is what Oryx (ZSA's graphical configurator) uses, so it's guaranteed to work.
- Make sure you've set up your environment per the [QMK docs](https://docs.qmk.fm/#/newbs_getting_started?id=set-up-your-environment) so compilation would actually work.
- Edit `qmk_path.txt` to have the actual path pointing to ZSA's `qmk_firmware/` repo. A common place is just `~/qmk_firmware/`

## Compiling
- Simply run `make` from the `src/` directory after finishing set up.

## Flashing

Here is the [original layout](https://configure.zsa.io/moonlander/layouts/XeXGP/jZlzM4/0) from Oryx.
