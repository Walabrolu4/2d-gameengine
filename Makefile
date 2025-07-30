build:
	#g++ -Wall -std=c++17 -I"./libs/" src/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 -o gameengine
	#g++ -Wall -std=c++17 src/*.cpp `sdl2-config --libs --cflags` -I"./libs/" -L./libs/ -llua -o gameengine
	#g++ -Wall -std=c++17 src/*.cpp `sdl2-config --libs --cflags` -I"./libs/" -I"./libs/lua" -L./libs -llua -o gameengine
	#g++ -Wall -std=c++17 -DSOL_USING_CXX_LUA=1 src/*.cpp `sdl2-config --libs --cflags` -I./libs -I./libs/lua -L./libs -llua -o gameengine
	g++ -Wall -std=c++17 -DSOL_NO_STD_OPTIMIZATIONS -DSOL_ALL_SAFETIES_ON=1 src/*.cpp `sdl2-config --libs --cflags` -I./libs -I./libs/lua -L./libs -llua -o gameengine


run:
	./gameengine

clean:
	rm gameengine
