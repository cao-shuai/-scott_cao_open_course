#
#makefile for build linkers and loaders
#


STATIC=libbuild_linkers_and_loaders.a
DYNAMIC=libbuild_linkers_and_loaders.so

DEBUG = -g -O0
NONEDEBUG = -O0
CC = gcc
AR = ar
INCLUDE = -I ../include/
DEFS = -D_GNU_SOURCE
CFLAGS = $(DEBUG) $(DEFS) -Wformat=2 -Wall -Wextra -Winline $(INCLUDE) -pipe -fPIC


#################################################################################
SRC = function_addr_demo.c


OBJ = $(SRC:.c=.o)

all:  $(DYNAMIC)

.PHONY: static
static : $(OBJ)
	$Q echo "[Link (Static)]"
	$Q $(AR) -r $(STATIC) $(OBJ) 

$(DYNAMIC): $(OBJ)
	$Q echo "[Link (Dynamic)]"
	$Q $(CC) -shared -o $(DYNAMIC) $(OBJ)

.c.o:
	$Q echo [Complie] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$Q echo "[clean]"
	$Q rm -rf $(OBJ) $(STATIC) $(DYNAMIC)
