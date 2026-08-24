# ================================================================
# Flexible Makefile for SDL2 Projects
#   - Use "make" to build main (default)
#   - Use "make TARGET=myapp" to build another name
# ================================================================

CXX = g++
CC = g++
CXXFLAGS = -std=c++17 -Wall -O2 \
           -I/opt/homebrew/opt/cppzmq/include \
           -I/opt/homebrew/opt/zeromq/include \
           -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE

LDFLAGS =  -L/opt/homebrew/opt/zeromq/lib -lzmq \
		   -L/opt/homebrew/lib -lSDL2main \
		   -L/opt/homebrew/lib -lSDL2

# Default target name (can be overridden)
TARGET ?= main

# Source files for the main target (restrict to main.cpp)
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

# ------------------------------------------------
# Build rules
# ------------------------------------------------
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)







# # ====== Project Config ======
# CXX      = g++
# CXXFLAGS = -std=c++17 -Wall -O2

# # ====== Homebrew Paths ======
# # Use /opt/homebrew on Apple Silicon (M1/M2/M3), /usr/local on Intel Macs
# BREW_PREFIX := $(shell brew --prefix)
# INCLUDES    := -I$(BREW_PREFIX)/opt/cppzmq/include \
#                -I$(BREW_PREFIX)/opt/zeromq/include \
# 			   -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
# LDFLAGS     := -L$(BREW_PREFIX)/opt/zeromq/lib -lzmq \
# 			   -L/opt/homebrew/lib -lSDL2main \
# 			   -L/opt/homebrew/lib -lSDL2

# # -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
# # -L/opt/homebrew/lib -lSDL2

# # ====== Targets ======
# TARGET = main
# SRC    = main.cpp

# # ====== Build Rules ======
# $(TARGET): $(SRC)
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LDFLAGS)

# clean:
# 	rm -f $(TARGET)
