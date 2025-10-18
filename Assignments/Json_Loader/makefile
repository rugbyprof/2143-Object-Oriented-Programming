# ====== Project Config ======
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -O2

# ====== Homebrew Paths ======
# Use /opt/homebrew on Apple Silicon (M1/M2/M3), /usr/local on Intel Macs
BREW_PREFIX := $(shell brew --prefix)
INCLUDES    := -Iincludes \
               -I$(BREW_PREFIX)/opt/cppzmq/include \
               -I$(BREW_PREFIX)/opt/zeromq/include
LDFLAGS     := -L$(BREW_PREFIX)/opt/zeromq/lib -lzmq

# ====== Targets ======
TARGET = example
SRC    = example.cpp

# ====== Build Rules ======
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)