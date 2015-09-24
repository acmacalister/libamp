# 
# Simple makefile to build inih as static library.
#

SRC = ./list.c ./string.c ./task.c
OBJ = $(SRC:.c=.o)
OUT = libamp.a
INCLUDES = -I..
CCFLAGS = -g -O2
CC = gcc
LDFLAGS = -g
INCLUDE_DIR = /usr/local/include/
#INSTALLDIR = ../binaries

.SUFFIXES: .c

default: $(OUT)

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) $(EXTRACCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ) $(EXTRAARFLAGS)

clean:
	rm -f $(OBJ) $(OUT)

install:
	mkdir -p $(INCLUDE_DIR)/amp
	cp -p *.h $(INCLUDE_DIR)/amp/
	# mkdir -p $(INSTALLDIR)
	# cp -p $(OUT) $(INSTALLDIR)