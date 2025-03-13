BUILD_DIR = game_build
TARGET = $(BUILD_DIR)/game
SRC_DIR = src
LIB_DIR = lib
IMGUI_DIR = ../imgui
IMGUI_BACKENDS_DIR = $(IMGUI_DIR)/backends

CPP_SOURCES := $(shell find $(SRC_DIR) -type f -name "*.cpp")

SOURCES = $(CPP_SOURCES)

CXX = g++
CXXFLAGS = -std=c++17 \
		   -I/usr/local/include/SDL2 \
		   -I/usr/local/include \
		   -I./include \
		   -I../include \
		   -D_REENTRANT \
		   -I$(IMGUI_DIR) \
		   -I$(IMGUI_BACKENDS_DIR)
LDFLAGS = -L/usr/local/lib \
		  -Wl,-rpath,/usr/local/lib \
		  -Wl,--enable-new-dtags \
		  -lSDL2 \
		  -lSDL2_image \
		  -L$(LIB_DIR) \
		  -ldengid \
		  -limgui

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
