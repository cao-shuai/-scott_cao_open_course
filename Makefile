#
# open course makefile
#
DEBUGMAKEFILE="TRUE"
ifdef DEBUGMAKEFILE
hide ?=@	
endif

ROOT_DIR=$(shell pwd)

##########################################################config gcc##########################################
ifdef DEBUGMAKEFILE
$(warning "build config gcc")
endif
MAKE=make
CC=gcc
DEBUG = -g -O0
AR = ar
INCLUDE = -I
DEFS = -D_GNU_SOURCE
CFLAGS = $(DEBUG) $(DEFS) -Wformat=2 -Wall -Wextra -Winline $(INCLUDE) $(ROOT_DIR)/include  -pipe -fPIC

##########################################################config output dir####################################
ifdef DEBUGMAKEFILE
$(warning "build output dir")
endif
OUT=$(ROOT_DIR)/out
OUT_SYMBOLES=$(OUT)/symbols
OUT_SYMBOLES_OBJ=$(OUT_SYMBOLES)/obj
OUT_SYMBOLES_DLIBS=$(OUT_SYMBOLES)/lib/dynamic
OUT_SYMBOLES_SLIBS=$(OUT_SYMBOLES)/lib/static
OUT_OBJ=$(OUT)/obj
OUT_LIB=$(OUT)/lib
OUT_DLIBS=$(OUT_LIB)/dynamic
OUT_SLIBS=$(OUT_LIB)/static
OUT_BIN=$(OUT)/bin

$(shell test -d $(OUT) || mkdir -p $(OUT))
$(shell test -d $(OUT_SYMBOLES) || mkdir -p $(OUT_SYMBOLES))
$(shell test -d $(OUT_SYMBOLES_OBJ) || mkdir -p $(OUT_SYMBOLES_OBJ))
$(shell test -d $(OUT_SYMBOLES_DLIBS) || mkdir -p $(OUT_SYMBOLES_DLIBS))
$(shell test -d $(OUT_SYMBOLES_SLIBS) || mkdir -p $(OUT_SYMBOLES_SLIBS))
$(shell test -d $(OUT_OBJ) || mkdir -p $(OUT_OBJ))
$(shell test -d $(OUT_DLIBS) || mkdir -p $(OUT_DLIBS))
$(shell test -d $(OUT_SLIBS) || mkdir -p $(OUT_SLIBS))
$(shell test -d $(OUT_BIN) || mkdir -p $(OUT_BIN))


#########################################################export para ###########################################

.PHONY: all build  release  clean

SUBMOUDLES:=$(ROOT_DIR)/build_linkers_and_loaders
SRC = main.c

MOUDSTATICNAME="main_static.bin"
MOUDDYNAMICNAME="main_dynamic.bin"

OBJ = $(SRC:.c=.o)

all:
	$(hide) echo "[all....]"
	$(hide) make clean
	$(hide) make build
	$(hide) make release
	$(hide) $(CC) $(OUT_SYMBOLES_OBJ)/main.o -L $(OUT_SYMBOLES_DLIBS) -lbuild_linkers_and_loaders $(INCLUDE) $(ROOT_DIR)/include/ction_addr_demo.h -o $(OUT_BIN)/$(MOUDDYNAMICNAME)
	$(hide) $(CC) $(OUT_SYMBOLES_OBJ)/main.o $(OUT_SYMBOLES_OBJ)/function_addr_demo.o -o $(OUT_BIN)/$(MOUDSTATICNAME)

build: $(OBJ)
	$(hide) echo "[building....]"
	$(hide) $(MAKE) -C $(SUBMOUDLES) all

.c.o:
	$(hide) echo "build main"
	$(hide) $(CC) -c $(CFLAGS) $< -o $(OUT_SYMBOLES_OBJ)/$@

release:
	$(hide) echo "[release....]"
	$(hide) $(MAKE) -C $(SUBMOUDLES) release
	$(hide) $(shell strip -s $(OUT_SYMBOLES_OBJ)/main.o -o $(OUT_OBJ)/main.o)

clean:
	$(hide) echo "[clean....]"
	$(hide) rm -rf $(OUT)
	$(hide) $(MAKE) -C build_linkers_and_loaders clean
