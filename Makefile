MAKEFLAGS += -r

BINDIR := bin
BIN := $(BINDIR)/fist
BIN_SOURCES := \
	fist/bst.c \
	fist/config.c \
	fist/dstring.c \
	fist/fist.c \
	fist/hashmap.c \
	fist/indexer.c \
	fist/serializer.c \
	fist/server.c \
	fist/tests.c \
	fist/lzf_c.c \
	fist/lzf_d.c

BIN_SOURCES_CHECK := \
	fist/bst.c \
	fist/config.c \
	fist/dstring.c \
	fist/fist.c \
	fist/hashmap.c \
	fist/indexer.c \
	fist/serializer.c \
	fist/server.c \
	fist/tests.c 

BIN_HEADER_SOURCES := \
	fist/bst.h \
	fist/dstring.h \
	fist/hashmap.h \
	fist/indexer.h \
	fist/serializer.h \
	fist/server.h \
	fist/version.h \
	fist/tests.h \
	fist/lzfP.h \
	fist/lzf.h


BIN_OBJECTS := $(BIN_SOURCES:=.o)
BIN_DEPS := $(BIN_SOURCES:=.d)

DESTDIR =
prefix = /usr/local

CC ?= gcc
CFLAGS ?= -Wall -O2 -g
CFLAGS += -std=c99 -D_DEFAULT_SOURCE
LDFLAGS ?=
LDLIBS :=
MKDIR ?= mkdir -p
RM ?= rm -f
CLANG_FORMAT ?= clang-format
DIFF ?= diff

.PHONY: all clean distclean

all: $(BIN)

$(BIN): $(BIN_OBJECTS)
	$(MKDIR) $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

test: $(BIN)
	cppcheck --quiet --std=c99 --enable=style,warning,performance,portability,unusedFunction --error-exitcode=1 $(BIN_SOURCES_CHECK)
	valgrind --suppressions=valgrind.supp --leak-check=full --error-exitcode=1  $(BIN) -t

.PHONY: test

%.c.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

check_format:
	$(foreach f, $(BIN_SOURCES), $(CLANG_FORMAT) $(f) | $(DIFF) -u $(f) -;)
	$(foreach f, $(BIN_HEADER_SOURCES), $(CLANG_FORMAT) $(f) | $(DIFF) -u $(f) -;)

format:
	$(foreach f, $(BIN_SOURCES), $(CLANG_FORMAT) -i $(f);)
	$(foreach f, $(BIN_HEADER_SOURCES), $(CLANG_FORMAT) -i $(f);)

.PHONY: format check_format

clean:
	-$(RM) $(BIN) $(BIN_OBJECTS) $(BIN_DEPS)

distclean: clean
	-$(RM) fist.db

.PHONY: install uninstall

install: $(BIN)
	install -D $(BIN) $(DESTDIR)$(prefix)/bin/fist

uninstall:
	-$(RM) $(DESTDIR)$(prefix)/bin/fist

-include $(BIN_DEPS)
