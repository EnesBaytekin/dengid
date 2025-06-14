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
#include <engine/object_loader.hpp>
#include <image/image_resource.hpp>
#include "imfilebrowser.hpp"
#include <engine/editor_utility.hpp>

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

    if (ImGui::Button("Open Project Folder")) {
        std::string project_path = project_manager.get_project_path();
        EditorUtility::open_folder(project_path);
    }

    ImGui::Dummy(ImVec2(0, 20));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 20));

    auto scene = app.get_main_scene();

    static ImGui::FileBrowser file_dialog(
        ImGuiFileBrowserFlags_EnterNewFilename |
        ImGuiFileBrowserFlags_CreateNewDir |
        ImGuiFileBrowserFlags_CloseOnEsc |
        ImGuiFileBrowserFlags_ConfirmOnEnter |
        ImGuiFileBrowserFlags_SkipItemsCausingError,
        project_manager.get_project_path()
    );

    if (ImGui::Button("Create Object from Template")) {
        file_dialog.Open();
    }
    file_dialog.Display();
    if (file_dialog.HasSelected()) {
        std::string template_name = file_dialog.GetSelected();
        auto new_object = ObjectLoader::load_object_from_template(template_name, Vector2(0, 0));
        scene->spawn_object(new_object);
        file_dialog.ClearSelected();
    }

    if (ImGui::Button("Create Object")) {
        auto object = std::make_shared<Object>();
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

    ImGui::SameLine();
    if (!is_object_selected) {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("Clone Object")) {
        json object_data = ObjectLoader::save_object(inspector->selected_object);
        auto new_object = ObjectLoader::load_object(object_data);
        std::string base_name = inspector->selected_object->name;
        size_t copy_pos = base_name.find(" (copy");
        if (copy_pos != std::string::npos) {
            base_name = base_name.substr(0, copy_pos);
        }

        int copy_count = 1;
        std::string new_name;
        bool name_exists;
        do {
            new_name = base_name + " (copy " + std::to_string(copy_count++) + ")";
            name_exists = false;
            for (const auto& obj : scene->get_objects()) {
                if (obj->name == new_name) {
                    name_exists = true;
                    break;
                }
            }
        } while (name_exists);

        new_object->name = new_name;
        scene->spawn_object(new_object);
        inspector->selected_object = new_object;
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
