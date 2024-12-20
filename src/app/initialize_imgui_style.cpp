#include "app/initialize_imgui_style.hpp"
#include "imgui.h"

void initialize_imgui_style() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 10.0f;
}
