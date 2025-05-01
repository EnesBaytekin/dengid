#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_hierarchy.hpp"
#include "imgui_windows/imgui_window_inspector.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <fstream>
#include <project/project_manager.hpp>
#include <engine/components/image_component.hpp>
#include <image/image_resource.hpp>

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
        ImGui::SetNextWindowSize(ImVec2(320.0f, (float)(height-18)));
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
    
    ImGui::SameLine();
    
    if (ImGui::Button("Save Scene")) {
        project_manager.save_project();
    }

    auto inspector = std::dynamic_pointer_cast<ImguiWindowInspector>(app.get_view()->get_window("inspector"));

    bool is_object_selected = inspector->selected_object != nullptr;
    if (!is_object_selected) {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("Delete Object")) {
        scene->delete_object(inspector->selected_object);
        inspector->selected_object = nullptr;
    }
    if (!is_object_selected) {
        ImGui::EndDisabled();
    }

    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    if (ImGui::CollapsingHeader("Objects##collapsing_header", ImGuiTreeNodeFlags_DefaultOpen)) {
        auto& objects = scene->get_objects();
        int index_to_move = -1;
        int index_target = -1;

        for (int i = 0; i < objects.size(); ++i) {
            auto& object = objects[i];
            const void* obj_address = object.get();
            char buffer[20];
            std::snprintf(buffer, sizeof(buffer), "%p", obj_address);
            std::string obj_id(buffer);

            bool selected = object == inspector->selected_object;
            std::string label = object->name + "##" + obj_id;

            ImGui::Selectable(label.c_str(), &selected);
            if (selected) {
                inspector->selected_object = object;
            }

            // DRAG SOURCE
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetDragDropPayload("OBJECT_INDEX", &i, sizeof(int));
                ImGui::Text("Move %s", object->name.c_str());
                ImGui::EndDragDropSource();
            }

            // DROP TARGET
            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECT_INDEX")) {
                    int src_index = *(const int*)payload->Data;
                    if (src_index != i) {
                        index_to_move = src_index;
                        index_target = i;
                    }
                }
                ImGui::EndDragDropTarget();
            }
        }

        if (index_to_move >= 0 && index_target >= 0) {
            auto obj = objects[index_to_move];
            objects.erase(objects.begin() + index_to_move);
            objects.insert(objects.begin() + index_target, obj);
        }
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

void ImguiWindowHierarchy::update() {
    AppMain& app = AppMain::get_instance();
    if (app.is_key_just_pressed(SDL_SCANCODE_DELETE)) {
        auto inspector = std::dynamic_pointer_cast<ImguiWindowInspector>(app.get_view()->get_window("inspector"));
        if (inspector->selected_object != nullptr) {
            auto scene = app.get_main_scene();
            scene->delete_object(inspector->selected_object);
            inspector->selected_object = nullptr;
        }
    }
}
