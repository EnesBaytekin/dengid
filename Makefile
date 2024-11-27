TARGET = build/main
SRC_DIR = src
INCLUDE_DIR = include
IMGUI_DIR = imgui
IMGUI_BACKENDS_DIR = $(IMGUI_DIR)/backends

CPP_SOURCES = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

IMGUI_SOURCES = $(IMGUI_DIR)/imgui.cpp \
                $(IMGUI_DIR)/imgui_draw.cpp \
                $(IMGUI_DIR)/imgui_widgets.cpp \
                $(IMGUI_DIR)/imgui_demo.cpp \
                $(IMGUI_DIR)/imgui_tables.cpp \
                $(IMGUI_BACKENDS_DIR)/imgui_impl_sdl2.cpp \
                $(IMGUI_BACKENDS_DIR)/imgui_impl_sdlrenderer2.cpp
                # $(IMGUI_BACKENDS_DIR)/imgui_impl_vulkan.cpp

SOURCES = $(CPP_SOURCES) $(IMGUI_SOURCES)

CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) \
           -I/usr/local/include/SDL2 \
           -D_REENTRANT \
           -I$(IMGUI_DIR) \
           -I$(IMGUI_BACKENDS_DIR)
LDFLAGS = -L/usr/local/lib \
          -Wl,-rpath,/usr/local/lib \
          -Wl,--enable-new-dtags \
          -lSDL2 \
          -lvulkan

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
