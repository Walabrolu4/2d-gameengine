CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
SOL_FLAGS = -DSOL_NO_STD_OPTIMIZATIONS -DSOL_ALL_SAFETIES_ON=1
SDL2 = `sdl2-config --libs --cflags`
INCLUDE_PATH = -I./libs -I./libs/lua

SRC_FILES = ./src/*.cpp \
						./src/Game/*.cpp \
						./src/Logger/*.cpp

LINKER_FLAGS = -L./libs -llua -lSDL2_image $(SDL2)
OBJECT_NAME = gameengine

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(SOL_FLAGS) $(SRC_FILES) $(INCLUDE_PATH) $(LINKER_FLAGS) -o $(OBJECT_NAME)

run:
	./$(OBJECT_NAME)

clean:
	rm $(OBJECT_NAME)

clean-build: clean build
