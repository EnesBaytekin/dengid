#include "app/app_main.hpp"
#include "app/app_implementation_sdlrenderer.hpp"
#include "path_utils.hpp"
#include "globals.hpp"

const std::filesystem::path HOME_DIRECTORY = get_home_directory();
const std::filesystem::path PROJECTS_DIRECTORY = get_projects_directory();

int main(int, char**) {
    AppImplementationSDLRenderer app_implementation("Dengid Engine", 1920, 1080);
    AppMain app(&app_implementation);
    app.run();
    return 0;
}
