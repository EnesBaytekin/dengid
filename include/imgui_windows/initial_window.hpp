#include "app/app_main.hpp"
#include "imgui.h"
#include "imfilebrowser.h"
#include <iostream>

void show_tab_item_create_project(AppMain& app) {
    if (ImGui::BeginTabItem("Create Project")) {

        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        ImGui::TextWrapped("Create a new project.");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        static char project_name[128] = "New Dengid Project";
        
        static char project_path[256];
        static bool initialize_project_path = false;
        if (!initialize_project_path) {
            strcpy(project_path, std::filesystem::current_path().string().c_str());
            initialize_project_path = true;
        }
        
        ImGui::Text("Project Name:");
        ImGui::InputText("##ProjectName", project_name, IM_ARRAYSIZE(project_name));
        
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        static ImGui::FileBrowser fileDialog(
            ImGuiFileBrowserFlags_SelectDirectory |
            ImGuiFileBrowserFlags_CreateNewDir |
            ImGuiFileBrowserFlags_HideRegularFiles |
            ImGuiFileBrowserFlags_SkipItemsCausingError
        );

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

        std::filesystem::path full_path = project_path;
        full_path.append(project_name);
        
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
            std::filesystem::create_directory(full_path);
        }

        if (name_is_empty || file_exists) {
            ImGui::EndDisabled();
        }

        ImGui::EndTabItem();
    }
}

void show_tab_item_load_project(AppMain& app) {
    if (ImGui::BeginTabItem("Load Project")) {

        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        ImGui::TextWrapped("Load an existing project.");


        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        ImVec2 window_size = ImGui::GetWindowSize();
        ImGui::SetCursorPosY(window_size.y-50);
        if (ImGui::Button("Load", ImVec2(-1, 40))) {
            std::cout << "Loading Project" << std::endl;
        }

        ImGui::EndTabItem();
    }
}


void show_initial_window(AppMain& app) {
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

    show_tab_item_load_project(app);
    show_tab_item_create_project(app);

    ImGui::EndTabBar();
    ImGui::End();
}