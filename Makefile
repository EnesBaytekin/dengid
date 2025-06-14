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
CXXFLAGS_COMMON = -std=c++17 \
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

CXXFLAGS_ENGINE = $(CXXFLAGS_COMMON) -MMD -MF $(OBJ_DIR)/engine/$(@F:.o=.d) -DBUILD_MODE__ENGINE
CXXFLAGS_NO_ENGINE = $(CXXFLAGS_COMMON) -MMD -MF $(OBJ_DIR)/lib/$(@F:.o=.d)

CPP_OBJS_ENGINE = $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/engine/%.o)
IMGUI_OBJS_ENGINE = $(IMGUI_SOURCES:$(IMGUI_DIR)/%.cpp=$(OBJ_DIR)/engine/%.o)
MAIN_OBJ_ENGINE = $(OBJ_DIR)/engine/main.o

CPP_OBJS_LIB = $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/lib/%.o)
IMGUI_OBJS_LIB = $(IMGUI_SOURCES:$(IMGUI_DIR)/%.cpp=$(OBJ_DIR)/lib/%.o)

all: $(TARGET) $(COMPILED_LIB_DIR)/libdengid.a

$(TARGET): $(CPP_OBJS_ENGINE) $(IMGUI_OBJS_ENGINE) $(MAIN_OBJ_ENGINE)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CPP_OBJS_ENGINE) $(IMGUI_OBJS_ENGINE) $(MAIN_OBJ_ENGINE) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/engine/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS_ENGINE)

$(OBJ_DIR)/engine/main.o: $(MAIN_CPP)
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS_ENGINE)

$(OBJ_DIR)/engine/%.o: $(IMGUI_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS_ENGINE)

$(COMPILED_LIB_DIR)/libdengid.a: $(CPP_OBJS_LIB) $(IMGUI_OBJS_LIB)
	mkdir -p $(COMPILED_LIB_DIR)
	ar rcs $(COMPILED_LIB_DIR)/libdengid.a $(CPP_OBJS_LIB)
	ar rcs $(COMPILED_LIB_DIR)/libimgui.a $(IMGUI_OBJS_LIB)

$(OBJ_DIR)/lib/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS_NO_ENGINE)

$(OBJ_DIR)/lib/%.o: $(IMGUI_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS_NO_ENGINE)

clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)
	rm -f $(COMPILED_LIB_DIR)/libdengid.a
	rm -f $(COMPILED_LIB_DIR)/libimgui.a

-include $(shell find $(OBJ_DIR) -type f -name "*.d")
.PHONY: all clean
