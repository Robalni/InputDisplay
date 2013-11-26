all: inputdisplay buttonmapper

inputdisplay:
	g++ -Iinclude `sdl-config --cflags` -Llib -o InputDisplay src/*.cpp `sdl-config --libs`

buttonmapper:
	g++ `sdl-config --cflags` -o buttonmapper buttonmapper-src/*.cpp `sdl-config --libs`

clean:
	rm -f InputDisplay buttonmapper
