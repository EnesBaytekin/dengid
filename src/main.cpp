#include "app/app_main.hpp"
#include "app/app_implementation_sdlrenderer.hpp"

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

void set_working_directory_to_executable() {
    char path[1024];
    
#ifdef _WIN32
    GetModuleFileNameA(NULL, path, sizeof(path));
#else
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (count != -1) {
        path[count] = '\0';
    }
#endif

    std::filesystem::path exe_path(path);
    std::filesystem::path exe_dir = exe_path.parent_path();

    std::filesystem::current_path(exe_dir);
}

int main(int, char**) {
    set_working_directory_to_executable();

    AppImplementationSDLRenderer app_implementation("Dengid Engine", 1920, 1080);
    AppMain app(&app_implementation);
    app.run();
    return 0;
}
