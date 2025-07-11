#include "imgui_windows/imgui_window_inspector.hpp"
#include <project/project_manager.hpp>
#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/script_component.hpp"
#include "engine/components/hitbox_component.hpp"
#include "engine/components/ysort_component.hpp"
#include "engine/components/component_draw_inspector_visitor.hpp"
#include "engine/editor_utility.hpp"
#include "engine/object_loader.hpp"
#include "imfilebrowser.hpp"

void ImguiWindowInspector::show() {
    if (!is_visible()) return;

    AppMain& app = AppMain::get_instance();
    ProjectManager& project_manager = ProjectManager::get_instance();

    static bool window_is_initialized = false;
    if (!window_is_initialized) {
        int width, height;
        SDL_GetWindowSize(app.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(width-320, 18));
        ImGui::SetNextWindowSize(ImVec2(320.0f, (float)(height-18)));
        window_is_initialized = true;
    }
    bool visible = true;
    ImGui::Begin("Inspector", &visible,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove
    );

    if (!visible) {
        set_visible(false);
    }
    
    ImGui::Dummy(ImVec2(0, 8));

    if (!selected_object) {
        ImGui::TextWrapped("%s", "No object is selected.");
    } else {
        const void* obj_address = selected_object.get();
        char buffer[20];
        std::snprintf(buffer, sizeof(buffer), "%p", obj_address);
        std::string obj_id(buffer);

        ImGui::Text("Object id: %s", obj_id.c_str());

        ImGui::Dummy(ImVec2(0, 8));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 8));

        static char name[32];
        if (selected_object->name != name) {
            strcpy(name, selected_object->name.c_str());
        }
        ImGui::Text("%s", "Name:");
        ImGui::SameLine();
        if (ImGui::InputText("##object_name", name, IM_ARRAYSIZE(name))) {
            selected_object->name = name;
        }

        ImGui::Dummy(ImVec2(0, 8));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 8));


        static ImGui::FileBrowser file_dialog(
            ImGuiFileBrowserFlags_EnterNewFilename |
            ImGuiFileBrowserFlags_CreateNewDir |
            ImGuiFileBrowserFlags_CloseOnEsc |
            ImGuiFileBrowserFlags_ConfirmOnEnter |
            ImGuiFileBrowserFlags_SkipItemsCausingError,
            project_manager.get_project_path()
        );

        static auto object_to_save = selected_object;
        
        if (ImGui::Button("Save as Template")) {
            std::cout << "project path: " << project_manager.get_project_path() << std::endl;
            object_to_save = selected_object;
            file_dialog.SetInputName(selected_object->name+".obte");
            file_dialog.Open();
        }
        file_dialog.Display();
        if (file_dialog.HasSelected()) {
            std::string template_name = file_dialog.GetSelected();
            std::cout << "Saving object to template: " << template_name << std::endl;
            ObjectLoader::save_object_to_template(object_to_save, template_name);
            file_dialog.ClearSelected();
        }

        ImGui::Dummy(ImVec2(0, 8));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 8));

        ImGui::Text("%s", "position: ");
        ImGui::SameLine();
        ImGui::DragFloat2(("##obj_inputs"+obj_id).c_str(), selected_object->position);

        ImGui::Text("%s", "depth: ");
        ImGui::SameLine();
        ImGui::DragInt("##obj_depth", &selected_object->depth, 0.1f, -65536, 65535);

        ComponentDrawInspectorVisitor visitor;
        int component_index = 0;
        IComponent* component_to_delete = nullptr;
        for (auto& component : selected_object->get_components()) {
            ImGui::Dummy(ImVec2(0, 8));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0, 8));

            std::string popup_name = "Delete Component##"+std::to_string(component_index);

            if (ImGui::Button(("x##delete_component_"+std::to_string(component_index)).c_str())) {
                ImGui::OpenPopup(popup_name.c_str());
            }
            ImGui::SameLine();

            component->accept_visitor(visitor);

            ImGui::SetNextWindowSize(ImVec2(200, 0));
            if (ImGui::BeginPopup(popup_name.c_str())) {
                ImGui::TextWrapped("Are you sure you want to delete this component?");
                ImGui::Separator();
                if (ImGui::Button("Yes", ImVec2(80, 0))) {
                    component_to_delete = component.get();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("No", ImVec2(80, 0))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ++component_index;
        }
        if (component_to_delete) {
            selected_object->remove_component(component_to_delete->get_type());
        }

        ImGui::Dummy(ImVec2(0, 8));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 8));

        std::map<ComponentType, std::string> component_list;
        component_list[ComponentType::IMAGE_COMPONENT] = "Image Component";
        component_list[ComponentType::SCRIPT_COMPONENT] = "Script Component";
        component_list[ComponentType::HITBOX_COMPONENT] = "Hitbox Component";
        component_list[ComponentType::YSORT_COMPONENT] = "Y-Sort Component";

        static ComponentType selected_component_type;
        static bool component_selection_popup_is_open = false;
        if (ImGui::Button("Add Component")) {
            component_selection_popup_is_open = true;
        }

        if (component_selection_popup_is_open) {
            ImGui::OpenPopup("Component Selection");
            component_selection_popup_is_open = false;
        }
        if (ImGui::BeginPopup("Component Selection")) {
            ImGui::Text("Select an component:");
            ImGui::Separator();

            for (auto [type, name] : component_list) {
                if (selected_object->has_component(type)) {
                    continue;
                }
                if (ImGui::Selectable(name.c_str(), selected_component_type == type)) {
                    selected_component_type = type;
                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }

        if (selected_component_type != ComponentType::NONE
        && !selected_object->has_component(selected_component_type)) {
            switch (selected_component_type) {
                case ComponentType::IMAGE_COMPONENT: {
                    selected_object->add_component(std::make_unique<ImageComponent>("icon.png"));
                    break;
                }
                case ComponentType::SCRIPT_COMPONENT: {
                    selected_object->add_component(std::make_unique<ScriptComponent>(""));
                    break;
                }
                case ComponentType::HITBOX_COMPONENT: {
                    auto rect = EditorUtility::get_object_rect(selected_object);
                    selected_object->add_component(std::make_unique<HitboxComponent>(0, 0, rect->w, rect->h));
                    break;
                }
                case ComponentType::YSORT_COMPONENT: {
                    auto rect = EditorUtility::get_object_rect(selected_object);
                    selected_object->add_component(std::make_unique<YSortComponent>());
                    break;
                }
            }
            selected_component_type = ComponentType::NONE;
        }
    }

    ImGui::End();
}
