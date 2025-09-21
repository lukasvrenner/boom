CFLAGS = -std=c17 -Wall -Wextra -Wpedantic
CFLAGS_DEBUG = $(CFLAGS) -g -O0
CFLAGS_RELEASE = $(CFLAGS) -O3

LDFLAGS = -lm
LDFLAGS_DEBUG = $(LDFLAGS)
LDFLAGS_RELEASE = $(LDFLAGS)

SRC = src/main.c src/matrix.c src/vector.c

OBJ_DEBUG = build/$(SRC:.c=.o)
DEP_DEBUG = $(OBJ_DEBUG:.o=.d)

OBJ_RELEASE = buildrel/$(SRC:.c=.o)
DEP_RELEASE = $(OBJ_RELEASE:.o=.d)

NAME = boom

all: debug

################
# DEBUG MODE #
################
debug: build/$(NAME)

build/$(NAME): $(OBJ_DEBUG)
	cc $(OBJ_DEBUG) $(LDFLAGS_DEBUG) -o build/$(NAME)

build/src/%.o: src/%.c | build/src
	cc $(CFLAGS_DEBUG) -MMD -MP -c $< -o $@

build/src:
	mkdir -p $@

-include $(DEP_DEBUG)

################
# RELEASE MODE #
################
release: buildrel/$(NAME)

buildrel/$(NAME): $(OBJ_RELEASE)
	cc $(OBJ_RELEASE) $(LDFLAGS_RELEASE) -o buildrel/$(NAME)

buildrel/src/%.o: src/%.c | buildrel/src
	cc $(CFLAGS_RELEASE) -MMD -MP -c $< -o $@

buildrel/src:
	mkdir -p $@

-include $(DEP_RELEASE)

clean:
	rm -rf build/
	rm -rf buildrel/

.PHONY: all debug release clean
