#include "app/app_main.hpp"
#include "imgui.h"
#include "imfilebrowser.h"
#include <iostream>

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
    
    ImGui::TextWrapped("Create a New Project");

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

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 20.0f));

    ImVec2 window_size = ImGui::GetWindowSize();
    ImGui::SetCursorPosY(window_size.y-50);
    if (ImGui::Button("Create", ImVec2(-1, 40))) {
        if (strlen(project_name) > 0 && strlen(project_path) > 0) {
            std::filesystem::path full_path = project_path;
            full_path.append(project_name);
            std::cout << "Creating project: " << full_path << std::endl;
        } else {
            std::cout << "Error: Project name or path is empty!" << std::endl;
        }
    }

    ImGui::End();
}