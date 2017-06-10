CC = gcc

all: default emptyasm stacknote forced-execstack forced-noexecstack

default: main.c
	$(CC) main.c -o default

emptyasm: main.c
	$(CC) main.c emptyasm.s -o emptyasm

stacknote: main.c stacknote.s
	$(CC) main.c stacknote.s -o stacknote

forced-execstack: main.c
	if $(CC) --version | grep clang > /dev/null; then \
	  as --execstack -o foox.o emptyasm.s; \
	else \
	  $(CC) -Wa,--execstack -c -o foox.o emptyasm.s; \
	fi; \
	$(CC) main.c foox.o -o forced-execstack && rm -f foox.o

forced-noexecstack: main.c
	if $(CC) --version | grep clang > /dev/null; then \
	  as --noexecstack -o foon.o emptyasm.s; \
	else \
	  $(CC) -Wa,--noexecstack -c -o foon.o emptyasm.s; \
	fi; \
	$(CC) main.c foon.o -o forced-noexecstack && rm -f foon.o

clean:
	rm -f default emptyasm stacknote forced-execstack forced-noexecstack
