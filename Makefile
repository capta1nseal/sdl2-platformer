COMPILER = g++
CFLAGS = -std=c++20 -O3
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image

INFILE = src/main.cpp
INCLUDES = src/gameApplication.cpp src/player.cpp
OUTFILE = bin/sdl2-platformer


$(OUTFILE): $(INFILE) $(INCLUDES)
	mkdir -p bin
	$(COMPILER) $(CFLAGS) -o $(OUTFILE) $(INFILE) $(LDFLAGS)

build: $(OUTFILE)
	cp -rf src/data bin

test: build
	cd bin; ../$(OUTFILE)

clean:
	rm -rf bin/*

update-assets:
	rm -rf bin/data
	cp -rf src/data bin/

.PHONY: build test clean update-assets
