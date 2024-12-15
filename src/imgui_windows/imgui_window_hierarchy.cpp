#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_hierarchy.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <fstream>
#include <project/project_manager.hpp>

#include <cstdlib>
#include <ctime>

int randrange(int start, int stop) {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(0)));
        initialized = true;
    }
    return start+rand()%(stop-start+1);
}

void show_hierarchy_window() {
    AppMain& app = AppMain::get_instance();
    ProjectManager& project_manager = ProjectManager::get_instance();

    static bool window_is_initialized = false;
    if (!window_is_initialized) {
        int width, height;
        SDL_GetWindowSize(app.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(0, 18));
        ImGui::SetNextWindowSize(ImVec2(256.0f, (float)(height-18)));
        window_is_initialized = true;
    }
    bool visible = true;
    ImGui::Begin("Hierarchy", &visible,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove
    );

    if (!visible) {
        auto window = app.get_view()->get_window("hierarchy");
        window->set_visible(false);
    }
    
    ImGui::Dummy(ImVec2(0, 20));

    ImGui::TextWrapped("%s", "Scene and objects are shown here.");

    ImGui::Dummy(ImVec2(0, 20));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 20));

    auto scene = app.get_main_scene();

    if (ImGui::Button("Create Object")) {
        int x = randrange(0, 1024);
        int y = randrange(0, 1024);
        auto object = std::make_shared<Object>(x, y);
        scene->spawn_object(object);
    }

    for (auto object : scene->get_objects()) {
        ImGui::Text("Object x: %f, y: %f", object->position.x, object->position.y);
    }

    if (ImGui::Button("Save Scene")) {
        project_manager.save_project();
    }

    ImGui::End();
}

void ImguiWindowHierarchy::show() {
    AppMain& app = AppMain::get_instance();
    auto window = app.get_view()->get_window("hierarchy");
    if (window->is_visible()) {
        show_hierarchy_window();
    }
}
