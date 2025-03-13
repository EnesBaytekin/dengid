BUILD_DIR = engine_build
TARGET = $(BUILD_DIR)/dengid
COMPILED_LIB_DIR = $(BUILD_DIR)/lib
OBJ_DIR = obj
SRC_DIR = src
INCLUDE_DIR = include
IMGUI_DIR = imgui
IMGUI_BACKENDS_DIR = $(IMGUI_DIR)/backends

CPP_SOURCES := $(filter-out $(SRC_DIR)/main.cpp, $(shell find $(SRC_DIR) -type f -name "*.cpp"))
MAIN_CPP = $(SRC_DIR)/main.cpp

IMGUI_SOURCES = $(IMGUI_DIR)/imgui.cpp \
				$(IMGUI_DIR)/imgui_draw.cpp \
				$(IMGUI_DIR)/imgui_widgets.cpp \
				$(IMGUI_DIR)/imgui_demo.cpp \
				$(IMGUI_DIR)/imgui_tables.cpp \
				$(IMGUI_BACKENDS_DIR)/imgui_impl_sdl2.cpp \
				$(IMGUI_BACKENDS_DIR)/imgui_impl_sdlrenderer2.cpp

CXX = g++
CXXFLAGS = -std=c++17 \
		   -I$(INCLUDE_DIR) \
		   -I/usr/local/include/SDL2 \
		   -D_REENTRANT \
		   -I$(IMGUI_DIR) \
		   -I$(IMGUI_BACKENDS_DIR) \
		   -pthread
LDFLAGS = -L/usr/local/lib \
		  -Wl,-rpath,/usr/local/lib \
		  -Wl,--enable-new-dtags \
		  -lSDL2 \
		  -lSDL2_image \
		  -pthread

CPP_OBJS = $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(OBJ_DIR)/main.o
IMGUI_OBJS = $(IMGUI_SOURCES:$(IMGUI_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET) $(COMPILED_LIB_DIR)/libdengid.a

$(TARGET): $(CPP_OBJS) $(IMGUI_OBJS) $(MAIN_OBJ)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CPP_OBJS) $(IMGUI_OBJS) $(MAIN_OBJ) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(MAIN_OBJ): $(MAIN_CPP)
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(IMGUI_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(COMPILED_LIB_DIR)/libdengid.a: $(CPP_OBJS) $(IMGUI_OBJS)
	mkdir -p $(COMPILED_LIB_DIR)
	ar rcs $(COMPILED_LIB_DIR)/libdengid.a $(CPP_OBJS)
	ar rcs $(COMPILED_LIB_DIR)/libimgui.a $(IMGUI_OBJS)
	rm -rf $(OBJ_DIR)

clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)
	rm -f $(COMPILED_LIB_DIR)/libdengid.a
	rm -f $(COMPILED_LIB_DIR)/libimgui.a

.PHONY: all clean
