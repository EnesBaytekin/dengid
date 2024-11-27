#include "app/app_main.hpp"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>

void AppMain::setup() {}

void AppMain::check_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            quit();
    }
}

void AppMain::update() {
    draw_rect(64, 128, 256, 256);

    static int nums[2];
    static int result = result;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(220, 720));
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

