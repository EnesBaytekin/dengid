TARGET = build/main
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
CXX = g++
CXXFLAGS = -Ilib/SDL2/build/include
LDFLAGS = -lSDL2 -Llib/SDL2/build/lib

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
