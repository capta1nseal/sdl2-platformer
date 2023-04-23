COMPILER = g++
CFLAGS = -std=c++20 -O3
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image

INFILE = src/main.cpp
INCLUDES = src/gameApplication.cpp src/math.cpp src/vec2.cpp src/input.cpp src/player.cpp src/camera.cpp src/rectCollider.cpp
OUTFILE = bin/sdl2-platformer
INDATA = src/data
OUTDATA = bin/data


$(OUTFILE): $(INFILE) $(INCLUDES)
	mkdir -p bin
	$(COMPILER) $(CFLAGS) -o $(OUTFILE) $(INFILE) $(LDFLAGS)

build: $(OUTFILE)
	rm -rf $(OUTDATA)
	cp -rf $(INDATA) bin/

test: build
	cd bin; ../$(OUTFILE)

clean:
	rm -rf bin/*


.PHONY: data build test clean
