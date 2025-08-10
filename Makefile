build:
	g++ -Wall -std=c++17 -DSOL_NO_STD_OPTIMIZATIONS -DSOL_ALL_SAFETIES_ON=1 \
	src/*.cpp `sdl2-config --libs --cflags` -I./libs -I./libs/lua \
	-L./libs -llua -lSDL2_image -o gameengine
run:
	./gameengine

clean:
	rm gameengine

clean-build: clean build
