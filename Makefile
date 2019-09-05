NAME = nextcom

BUILD_DIR ?= ./BUILD-$(NAME)
TMP_DIR ?= ./TMP-$(NAME)
SRC_DIRS ?= ./src
DOCS_DIR ?= ./docs
FILES_DIR ?= ./dist
RELEASE_DIR ?= ./RELEASE-$(NAME)
PUBLIC_DIR ?= $(RELEASE_DIR)/PUBLIC/$(NAME)
PLUGIN_DIR ?= ./plugins
DEV_DIR ?= $(RELEASE_DIR)/DEV
GITHUB_DIR ?= $(RELEASE_DIR)/GITHUB

LIBSPRITE := ./zxnext_sprite
LIBSPRITE_INCLUDE := $(LIBSPRITE)/include
LIBSPRITE_LIB := $(LIBSPRITE)/lib/sccz80

LIBLAYER2 := ./zxnext_layer2
LIBLAYER2_INCLUDE := $(LIBLAYER2)/include
LIBLAYER2_LIB := $(LIBLAYER2)/lib/sccz80

DEBUGFLAGS := --list --c-code-in-asm

CC=zcc
CCFLAGS=+zxn -vn -O3 -startup=1 -clib=new
LDFLAGS=-lm \

INCFLAGS=

BUILDFLAGS := -DPLOTIT_BUILD_NUMBER=\"`git rev-list --count HEAD`\" -DPLOTIT_BUILD_DATE=\"date\"

SH := /bin/sh
CD := cd
RSYNC := rsync -parv
MKDIR := mkdir -p
RM := rm -rf
LSH := ls -larth
CP := cp -rv
MV := mv
CAT := `which cat`
SED := `which sed`
LS := ls -l@k

ZIP := zip -r -v

DEBUGFLAGS := --list --c-code-in-asm

all: dirs media app

app: binaries

dirs:
	$(MKDIR) $(BUILD_DIR)
	$(MKDIR) $(TMP_DIR)

binaries:
	$(CC) $(CCFLAGS) -m $(DEBUG) $(LDFLAGS) $(INCFLAGS) $(BUILDFLAGS) \
		-pragma-include:zpragma.inc  -Cz"--clean --fullsize --main-fence 0xC000" \
		@$(NAME).lst -o$(NAME) -subtype=nex  -create-app
	$(MV) $(NAME).nex $(BUILD_DIR)
	$(LSH) $(BUILD_DIR)/$(NAME).nex
	$(RM) $(TMP_DIR)/*.o

media:
	$(CP) $(FILES_DIR)/* $(BUILD_DIR)

debug: DEBUG = $(DEBUGFLAGS)

debug: all

clean:
	$(RM) tmp zcc_opt.def zcc_proj.lst src/*.lis $(BUILD_DIR) $(TMP_DIR) plotit.tap plotit*.bin plotit.map

emulate:
	mono /u/ZX/CSpect/CSpect.exe -nosound -r -w4 -zxnext -mmc=$(BUILD_DIR) $(BUILD_DIR)/$(NAME).nex

mkdir:
	$(MKDIR) /Volumes/airflash/$(NAME)

install: mkdir
	$(CP) $(BUILD_DIR)/* /Volumes/airflash/$(NAME)

update:
	$(CP) $(BUILD_DIR)/$(NAME).nex /Volumes/airflash/$(NAME)

dev:
	$(RM) $(DEV_DIR)/$(NAME)*
	$(MKDIR) $(DEV_DIR)/$(NAME)
	$(CP) $(BUILD_DIR)/* $(DEV_DIR)/$(NAME)
	$(MKDIR) $(DEV_DIR)/$(NAME)/dev
	$(CP) $(PLUGIN_DIR)/. $(DEV_DIR)/$(NAME)/dev
	$(CD) $(DEV_DIR)/ && $(ZIP) $(NAME).zip $(NAME)/
	$(MV) $(DEV_DIR)/$(NAME).zip $(DEV_DIR)/$(NAME).jpg
	$(CD) $(DEV_DIR)/ && $(ZIP) $(NAME).zip $(NAME).jpg README.txt
	open $(DEV_DIR)/

github:
	$(CP) $(BUILD_DIR)/* $(GITHUB_DIR)
	$(CD) $(GITHUB_DIR) && git pull \
	                 && git add * \
	                 && git commit

release:

	$(CD) $(GITHUB_DIR)/.. && $(RM) $(NAME).zip \
	                       && git clone --branch=master GITHUB $(NAME) \
	                       && $(RM) $(NAME)/.git \
                           && $(ZIP) $(NAME).zip $(NAME)/ \
                           && $(RM) $(NAME)