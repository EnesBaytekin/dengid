#include "main_app.hpp"
#include <iostream>

void MainApp::start_up() {}

void MainApp::update() {
    static int nums[2];
    static int result = result;
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(220, h));
    ImGui::Begin("Some window", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse);
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("First number", &nums[0]);
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("Second number", &nums[1]);
    if (ImGui::Button("Sum")) {
        result = nums[0]+nums[1];
    }
    ImGui::Text(("Result: "+std::to_string(result)).c_str());
    ImGui::End();
}
