CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = src/main.c
BIN = sifetch
PREFIX = /usr/local

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

install: $(BIN)
	install -d $(PREFIX)/bin
	install -m 755 $(BIN) $(PREFIX)/bin

clean:
	rm -f $(BIN)

.PHONY: all install clean
