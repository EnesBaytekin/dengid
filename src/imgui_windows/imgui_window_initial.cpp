#include "imgui_windows/imgui_window_initial.hpp"
#include "app/app_main.hpp"
#include "imgui.h"
#include "imfilebrowser.hpp"
#include <iostream>
#include "globals.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <fstream>
#include "project/project_manager.hpp"
#include "image/image_resource.hpp"

void create_projects_folder_if_not_exist() {
    if (!std::filesystem::exists(PROJECTS_DIRECTORY)) {
        std::filesystem::create_directories(PROJECTS_DIRECTORY);
    }
}

std::vector<std::filesystem::path> get_projects() {
    std::vector<std::filesystem::path> projects;
    for (auto& project : std::filesystem::directory_iterator(PROJECTS_DIRECTORY)) {
        if (std::filesystem::is_directory(project)) {
            projects.push_back(project);
        }
    }
    return projects;
}

void load_project(const std::filesystem::path& project_path) {
    AppMain& app = AppMain::get_instance();
    app.set_view(EnumAppViewType::PROJECT_VIEW);

    ProjectManager& project_manager = ProjectManager::get_instance();
    project_manager.set_project_path(project_path);
    
    project_manager.load_project();

    std::system("make clean");
}

void create_project(const std::filesystem::path& project_path) {
    std::filesystem::create_directory(project_path);
    std::filesystem::copy_file(EXECUTABLE_DIRECTORY/"icon.png", project_path/"icon.png");

    std::ofstream scene_file(project_path/"main_scene.data");
    scene_file.close();

    load_project(project_path);
}

void show_tab_item_create_project() {
    AppMain& app = AppMain::get_instance();
    
    if (ImGui::BeginTabItem("Create Project")) {

        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        ImGui::TextWrapped("%s", "Create a new project.");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        static char project_name[128] = "New Dengid Project";
        
        static char project_path[256];
        static bool initialize_project_path = false;
        if (!initialize_project_path) {
            strcpy(project_path, PROJECTS_DIRECTORY.string().c_str());
            initialize_project_path = true;
        }
        
        ImGui::Text("%s", "Project Name:");
        ImGui::InputText("##ProjectName", project_name, IM_ARRAYSIZE(project_name));
        
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        static ImGui::FileBrowser fileDialog(
            ImGuiFileBrowserFlags_SelectDirectory |
            ImGuiFileBrowserFlags_CreateNewDir |
            ImGuiFileBrowserFlags_HideRegularFiles |
            ImGuiFileBrowserFlags_SkipItemsCausingError,
            PROJECTS_DIRECTORY);

        ImGui::Text("Project Location:");
        ImGui::InputText("##ProjectPath", project_path, IM_ARRAYSIZE(project_path),
            ImGuiInputTextFlags_ReadOnly);
        ImGui::SameLine();
        
        if (ImGui::Button("Browse")) {
            fileDialog.Open();
        }
        fileDialog.Display();
        if (fileDialog.HasSelected()) {
            strcpy(project_path, fileDialog.GetSelected().string().c_str());
            fileDialog.ClearSelected();
        }

        std::filesystem::path full_path = (std::filesystem::path)project_path/project_name;
        
        bool file_exists = std::filesystem::exists(full_path);
        bool name_is_empty = strlen(project_name) == 0;
        
        ImGui::Dummy(ImVec2(0.0f, 10.0f));

        if (name_is_empty) {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "The project name cannot be empty!");
        } else if (file_exists) {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "There is already a project with this name!");
        } else {
            float line_height = ImGui::GetTextLineHeight();
            ImGui::Dummy(ImVec2(0.0f, line_height));
        }

        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        if (name_is_empty || file_exists) {
            ImGui::BeginDisabled();
        }

        ImVec2 window_size = ImGui::GetWindowSize();
        ImGui::SetCursorPosY(window_size.y-50);
        if (ImGui::Button("Create", ImVec2(-1, 40))) {
            create_project(full_path);
        }

        if (name_is_empty || file_exists) {
            ImGui::EndDisabled();
        }

        ImGui::EndTabItem();
    }
}

void show_tab_item_load_project() {
    AppMain& app = AppMain::get_instance();

    if (ImGui::BeginTabItem("Load Project")) {

        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        ImGui::TextWrapped("Load an existing project.");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        static int selection_index = -1;

        static bool refreshed = true;

        static std::vector<std::filesystem::path> projects;
        if (ImGui::Button("Refresh")) {
            refreshed = true;
        }

        if (refreshed) {
            projects = get_projects();
            selection_index = -1;
            refreshed = false;
        }

        if (ImGui::BeginListBox("##ListBox", ImVec2(-1, 300))) {
            ImVec2 selectables_origin = ImGui::GetCursorScreenPos();
            ImVec2 selectable_size(0.0f, 40.0f);

            for (int i=0; i<projects.size(); ++i) {
                auto project = projects[i];
                bool item_is_selected = selection_index == i;

                ImVec2 selectable_pos(selectables_origin.x, selectables_origin.y+i*selectable_size.y);

                ImGui::SetCursorScreenPos(ImVec2(
                    selectable_pos.x,
                    selectable_pos.y
                ));

                if (ImGui::Selectable(("##selectable_"+project.string()).c_str(), &item_is_selected,
                    ImGuiSelectableFlags_AllowDoubleClick,
                    selectable_size))
                {
                    selection_index = i;
                }

                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                    load_project(projects[selection_index]);
                }
                
                std::string icon_id = project/"icon.png";
                ImGui::SetCursorScreenPos(ImVec2(
                    selectable_pos.x+4,
                    selectable_pos.y+4
                ));
                app.draw_imgui_image(icon_id, 32, 32);
                
                ImGui::SetCursorScreenPos(ImVec2(
                    selectable_pos.x+44,
                    selectable_pos.y+selectable_size.y*0.5f-ImGui::GetTextLineHeight()
                ));
                ImGui::Text("%s", project.filename().string().c_str());
                
                ImGui::SetCursorScreenPos(ImVec2(
                    selectable_pos.x+44,
                    selectable_pos.y+selectable_size.y*0.5f
                ));
                ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "%s", project.string().c_str());
                
                ImGui::Dummy(ImVec2(0, 10));
            }
            ImGui::EndListBox();
        }

        ImVec2 window_size = ImGui::GetWindowSize();
        ImGui::SetCursorPosY(window_size.y-50);

        bool selected_project_exists = selection_index != -1 && std::filesystem::exists(projects[selection_index]);

        if (!selected_project_exists) {
            ImGui::BeginDisabled();
        }

        if (ImGui::Button("Load", ImVec2(-1, 40))) {
            load_project(projects[selection_index]);
        }

        if (!selected_project_exists) {
            ImGui::EndDisabled();
        }

        ImGui::EndTabItem();
    }
}

void ImguiWindowInitial::show() {
    AppMain& app = AppMain::get_instance();

    int width, height;
    SDL_GetWindowSize(app.window, &width, &height);
    ImGui::SetNextWindowPos({(float)width/4, (float)height/4});
    ImGui::SetNextWindowSize({(float)width/2, (float)height/2});
    ImGui::Begin("Initial Window", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar
    );    
    ImGui::BeginTabBar("##initial_window_tab_bar");

    create_projects_folder_if_not_exist();

    show_tab_item_load_project();
    show_tab_item_create_project();

    ImGui::EndTabBar();
    ImGui::End();
}
