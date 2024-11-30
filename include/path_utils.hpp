#ifndef PATH_UTILS_HPP
#define PATH_UTILS_HPP

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

std::filesystem::path get_executable_directory() {
    char path[1024];
    
#ifdef _WIN32
    GetModuleFileNameA(NULL, path, sizeof(path));
#else
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path)-1);
    if (count != -1) {
        path[count] = '\0';
    }
#endif

    std::filesystem::path exe_path(path);
    std::filesystem::path exe_dir = exe_path.parent_path();

    return exe_dir;
}

std::filesystem::path get_home_directory() {
    const char* home_dir = nullptr;

#ifdef _WIN32
    home_dir = getenv("USERPROFILE"); // Windows
#else
    home_dir = getenv("HOME"); // Linux/macOS
#endif

    std::filesystem::path home_path(home_dir);
    return home_path;
}

std::filesystem::path get_projects_directory() {
    std::filesystem::path projects_dir = get_home_directory();
    projects_dir.append("dengid-projects");
    return projects_dir;
}

#endif
