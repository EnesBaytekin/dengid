BUILD_DIR = game_build
TARGET = $(BUILD_DIR)/game
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = $(BUILD_DIR)/obj
SCRIPT_DIR = $(BUILD_DIR)/scripts
IMGUI_DIR = ../imgui
IMGUI_BACKENDS_DIR = $(IMGUI_DIR)/backends

CPP_SOURCES := $(shell find $(SRC_DIR) -type f -name "*.cpp")

SCRIPT_SOURCES := $(shell find $(SCRIPT_DIR) -type f -name "*.cpp")

CXX = g++
CXXFLAGS = -std=c++17 \
		   -I/usr/local/include/SDL2 \
		   -I/usr/local/include \
		   -I./include \
		   -I../include \
		   -D_REENTRANT \
		   -I$(IMGUI_DIR) \
		   -I$(IMGUI_BACKENDS_DIR) \
		   -MMD -MF $(OBJ_DIR)/$(@F:.o=.d)
LDFLAGS = -L/usr/local/lib \
		  -Wl,-rpath,/usr/local/lib \
		  -Wl,--enable-new-dtags \
		  -lSDL2 \
		  -lSDL2_image \
		  -L$(LIB_DIR) \
		  -ldengid \
		  -limgui

CPP_OBJS = $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SCRIPT_OBJS = $(SCRIPT_SOURCES:$(SCRIPT_DIR)/%.cpp=$(BUILD_DIR)/obj/%.o)

all: $(TARGET)

$(TARGET): $(CPP_OBJS) $(SCRIPT_OBJS)
	$(CXX) $(CPP_OBJS) $(SCRIPT_OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/obj/%.o: $(SCRIPT_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

-include $(shell find $(OBJ_DIR) -type f -name "*.d")

.PHONY: all clean
