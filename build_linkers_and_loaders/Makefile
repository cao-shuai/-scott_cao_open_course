#
#makefile for build linkers and loaders
#
CURDIR=$(shell pwd)
MOUDLE = build_linkers_and_loaders


STATICLIB=libbuild_linkers_and_loaders.a
DYNAMICLIB=libbuild_linkers_and_loaders.so

DEBUG = -g -O0
CC = gcc
AR = ar
INCLUDE = -I ../include/
DEFS = -D_GNU_SOURCE
CFLAGS = $(DEBUG) $(DEFS) -Wformat=2 -Wall -Wextra -Winline $(INCLUDE) -pipe -fPIC


#################################################################################
SRC = function_addr_demo.c


OBJ = $(SRC:.c=.o)

.PHONY: all clean

all:  $(DYNAMICLIB) $(STATICLIB)
	$Q echo "[mv obj to out]"
	$Q mv -f *.o $(CURDIR)/../out/symbols/obj/

$(STATICLIB) : $(OBJ)
	$Q echo "[Link build_linkers_and_loaders Static lib]"
	$Q $(AR) -r $(CURDIR)/../out/symbols/lib/static/$(STATICLIB) $(OBJ)

$(DYNAMICLIB): $(OBJ)
	$Q echo "[Link build_linkers_and_loaders Dynamic lib]"
	$Q $(CC) -shared -o $(CURDIR)/../out/symbols/lib/dynamic/$(DYNAMICLIB) $(OBJ)

.c.o:
	$Q echo [Complie build_linkers_and_loaders] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

clean:
	$Q echo "[clean build_linkers_and_loaders]"
