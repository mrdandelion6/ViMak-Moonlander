# typicaly at ~/qmk_firmware/
QMK_DIR := $(shell cat ../qmk_path.txt | sed 's:^\~:$(HOME):' | sed 's:/*$$:/:')

# where qmk needs source files to be
TARGET_DIR := $(QMK_DIR)keyboards/zsa/moonlander/keymaps/vimak/

# where we want to keep our binaries
BUILD_DIR = ../build/

# binary name
BIN_NAME = zsa_moonlander_vimak.bin

# compile firmware and make compile_commands.json for lsp.
$(BUILD_DIR)$(BIN_NAME): keymap.c config.h rules.mk
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(BUILD_DIR)
	@cp keymap.c config.h rules.mk $(TARGET_DIR)
	@echo "Generating compilation database..."
	@cd $(QMK_DIR) && qmk generate-compilation-database -kb moonlander -km vimak
	@echo "Copying compile_commands.json to current directory..."
	@cp $(QMK_DIR)compile_commands.json ./
	@echo "Compiling firmware..."
	@qmk compile -kb moonlander -km vimak
	@mv $(QMK_DIR)$(BIN_NAME) $(BUILD_DIR)

.PHONY: compile-db all clean

# generate compilation database only (without building)
compile-db:
	@mkdir -p $(TARGET_DIR)
	@cp keymap.c config.h rules.mk $(TARGET_DIR)
	@echo "Generating compilation database..."
	@cd $(QMK_DIR) && qmk generate-compilation-database -kb moonlander -km vimak
	@echo "Copying compile_commands.json to current directory..."
	@cp $(QMK_DIR)compile_commands.json ./

all: $(BUILD_DIR)$(BIN_NAME)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f compile_commands.json
