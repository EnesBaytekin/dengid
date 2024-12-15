#ifndef PROJECT_MANAGER_HPP
#define PROJECT_MANAGER_HPP

#include "project/project_settings.hpp"
#include <filesystem>

class ProjectManager {
private:
    ProjectSettings project_settings;
    std::filesystem::path project_path;

    ProjectManager() = default;
    ~ProjectManager() = default;
public:
    ProjectManager(const ProjectManager&) = delete;
    ProjectManager& operator=(const ProjectManager&) = delete;
    
    static ProjectManager& get_instance() {
        static ProjectManager instance;
        return instance;
    }
    
    void                  set_project_path(const std::filesystem::path& new_path) { project_path = new_path; }
    std::filesystem::path get_project_path() { return project_path; }
    ProjectSettings       get_project_settings() { return project_settings; }

    void load_project();
    void save_project();
};

#endif