CC = gcc
CFLAGS = -Wall
TARGET = cinit
SRCDIR = ./src
BINDIR = ./bin
SRC = $(SRCDIR)/cinit.c
OBJ = $(SRCDIR)/cinit.o
INSTALL_PATH = /usr/local/bin

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@

$(SRCDIR)/cinit.o: $(SRCDIR)/cinit.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(BINDIR)/$(TARGET)

install: $(BINDIR)/$(TARGET)
	cp $(BINDIR)/$(TARGET) $(INSTALL_PATH)

.PHONY: all clean install
