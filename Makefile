TARGET = build/main
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) /imgui/imgui.cpp /imgui/imgui_draw.cpp /imgui/imgui_widgets.cpp /imgui/imgui_demo.cpp /imgui/imgui_tables.cpp /imgui/backends/imgui_impl_sdl2.cpp /imgui/backends/imgui_impl_vulkan.cpp
CXX = g++
CXXFLAGS = -I/usr/local/include/SDL2 -D_REENTRANT -I/imgui -I/imgui/backends
LDFLAGS = -L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lvulkan

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
