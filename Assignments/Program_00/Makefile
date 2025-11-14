# =========================================================
# SDL2 + SDL_ttf Example Makefile
# =========================================================

CXX := g++
CXXFLAGS := -Wall -std=c++17 $(shell pkg-config --cflags sdl2 SDL2_ttf)
LDFLAGS := $(shell pkg-config --libs sdl2 SDL2_ttf)

TARGET := program00
SRC := main.cpp

# Default rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean