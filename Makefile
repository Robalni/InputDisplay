all:
	g++ -Iinclude `sdl-config --cflags` -Llib -o InputDisplay src/*.cpp `sdl-config --libs`

clean:
	rm -f InputDisplay
