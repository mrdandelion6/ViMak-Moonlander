# typicaly at ~/qmk_firmware/
QMK_DIR := $(shell cat ../qmk_path.txt | sed 's:^\~:$(HOME):' | sed 's:/*$$:/:')

# where qmk needs source files to be
TARGET_DIR := $(QMK_DIR)keyboards/zsa/moonlander/keymaps/vimak/

# where we want to keep our binaries
BUILD_DIR = ../build/

# binary name
BIN_NAME = zsa_moonlander_vimak.bin

$(BUILD_DIR)$(BIN_NAME): keymap.c config.h rules.mk
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(BUILD_DIR)
	@cp keymap.c config.h rules.mk $(TARGET_DIR)
	@qmk compile -kb moonlander -km vimak
	@mv $(QMK_DIR)$(BIN_NAME) $(BUILD_DIR)

.PHONY: all clean

all: $(BUILD_DIR)$(BIN_NAME)

clean:
	@rm -rf $(BUILD_DIR)
