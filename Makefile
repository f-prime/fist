MAKEFLAGS += -r

BINDIR := bin
BIN := $(BINDIR)/fist
BIN_SOURCES := \
	fist/dstring.c \
	fist/fist.c \
	fist/hashmap.c \
	fist/indexer.c \
	fist/serializer.c \
	fist/server.c \
	fist/tests.c \
	fist/utils.c
BIN_OBJECTS := $(BIN_SOURCES:=.o)
BIN_DEPS := $(BIN_SOURCES:=.d)

CC ?= gcc
CFLAGS ?= -Wall -O2 -g
CFLAGS += -std=c99
LDFLAGS ?=
LDLIBS :=
MKDIR ?= mkdir -p
RM ?= rm -f

.PHONY: all clean

all: $(BIN)

$(BIN): $(BIN_OBJECTS)
	$(MKDIR) $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

test: $(BIN)
	cppcheck --quiet --std=c99 --enable=style,warning,performance,portability,unusedFunction --error-exitcode=1 $(BIN_SOURCES)
	valgrind --log-file=valgrind.log --leak-check=full --error-exitcode=1  $(BIN) test

.PHONY: test

%.c.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) $(BIN) $(BIN_OBJECTS) $(BIN_DEPS)

-include $(BIN_DEPS)
