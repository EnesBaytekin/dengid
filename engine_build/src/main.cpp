#include "engine/scene.hpp"
#include "engine/object.hpp"
#include "app/app_implementation_sdlrenderer.hpp"
#include "path_utils.hpp"
#include "globals.hpp"

const std::filesystem::path HOME_DIRECTORY = get_home_directory();
const std::filesystem::path PROJECTS_DIRECTORY = get_projects_directory();
const std::filesystem::path EXECUTABLE_DIRECTORY = get_executable_directory();

int main(int, char**) {
    AppImplementationSDLRenderer app_implementation("Dengid Game", 640, 360);
    AppMain& app = AppMain::get_instance();
    app.initialize(&app_implementation);
    
    auto main_scene = std::make_shared<Scene>();
    auto object = std::make_shared<Object>();
    main_scene->spawn_object(object);
    app.set_main_scene(main_scene);
    
    app.run();
    return 0;
}
