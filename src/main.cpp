#include "app/app_main.hpp"
#include "app/app_implementation_sdlrenderer.hpp"

int main(int, char**) {
    AppImplementationSDLRenderer app_implementation("Dengid Engine", 1920, 1080);
    AppMain app(&app_implementation);
    app.run();
    return 0;
}
