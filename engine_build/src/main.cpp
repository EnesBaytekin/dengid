#include "engine/scene.hpp"
#include "engine/object.hpp"
#include "app/app_implementation_sdlrenderer.hpp"
#include "path_utils.hpp"
#include "globals.hpp"
#include "project/project_manager.hpp"
#include <iostream>
#include "project_settings_macro.hpp"

const std::filesystem::path HOME_DIRECTORY = get_home_directory();
const std::filesystem::path PROJECTS_DIRECTORY = get_projects_directory();
const std::filesystem::path EXECUTABLE_DIRECTORY = get_executable_directory();

int main(int, char**) {
    std::filesystem::path project_path = PROJECT_PATH;
    std::string project_name = project_path.filename().string();

    AppImplementationSDLRenderer app_implementation(project_name, WINDOW_WIDTH, WINDOW_HEIGHT);
    AppMain& app = AppMain::get_instance();
    app.initialize(&app_implementation);
    
    ProjectManager& project_manager = ProjectManager::get_instance();
    project_manager.set_project_path(project_path);
    project_manager.load_project(false);
    
    app.set_main_scene(app.get_main_scene());
    
    app.run();
    return 0;
}
