CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
SOL_FLAGS = -DSOL_NO_STD_OPTIMIZATIONS -DSOL_ALL_SAFETIES_ON=1
SDL2 = `sdl2-config --libs --cflags`

UNAME_S := $(shell uname -s)


LUA_INC ?=
LUA_LIB ?= -llua


ifeq ($(UNAME_S),Linux)
  ifneq ($(wildcard /usr/include/lua5.4),)
    LUA_INC := -I/usr/include/lua5.4   # Where Lua 5.4 headers live on Ubuntu/Pop!_OS
    LUA_LIB := -llua5.4                # Link the versioned library
  else ifneq ($(wildcard /usr/include/lua5.3),)
    LUA_INC := -I/usr/include/lua5.3
    LUA_LIB := -llua5.3
  endif
endif

INCLUDE_PATH = -I./libs -I./libs/lua $(LUA_INC)

SRC_FILES = ./src/*.cpp \
						./src/Game/*.cpp \
						./src/Logger/*.cpp \
						./src/ECS/*.cpp


LINKER_FLAGS = -L./libs $(LUA_LIB) -lSDL2_image $(SDL2)
OBJECT_NAME = gameengine

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(SOL_FLAGS) $(SRC_FILES) $(INCLUDE_PATH) $(LINKER_FLAGS) -o $(OBJECT_NAME)

run:
	./$(OBJECT_NAME)

clean:
	rm $(OBJECT_NAME)

clean-build: clean build
