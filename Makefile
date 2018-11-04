## Makefile un peu barbare mais efficace

# Params
CC=gcc
LD=gcc
CFLAGS=-Wall -W -Werror
LDFLAGS=

# Output executable
EXE=main
CFILES=$(wildcard *.c)
OBJS=$(CFILES:.c=.o)

.DEFAULT_GOAL := main

.PHONY: clean

all: main

main: main.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

# clean execution trace
clean :
	$(RM) $(EXE) $(OBJS)
