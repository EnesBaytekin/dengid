#ifndef APP_MAIN_HPP
#define APP_MAIN_HPP

#include "app/i_app_abstraction.hpp"
#include "app_views/enum_app_view_type.hpp"
#include <filesystem>
#include <map>
#include "project/project_settings.hpp"

class AppView;

class AppMain: public IAppAbstraction {
private:
    EnumAppViewType current_view_type;
    std::map<EnumAppViewType, std::shared_ptr<AppView>> views;
    std::filesystem::path project_path;
    ProjectSettings project_settings;
public:
    
    AppMain(IAppImplementation* _implementation):
        IAppAbstraction(_implementation),
        current_view_type(EnumAppViewType::INITIAL_VIEW) {}
    ~AppMain() = default;

    void                     add_view(const EnumAppViewType& type, std::shared_ptr<AppView> view) { views.insert({type, view}); }
    void                     set_view(const EnumAppViewType& type) { current_view_type = type; }
    std::shared_ptr<AppView> get_view() { return views[current_view_type]; }
    void                  set_project_path(const std::filesystem::path& new_path) { project_path = new_path; }
    std::filesystem::path get_project_path() { return project_path; }
    ProjectSettings get_project_settings() { return project_settings; }

    void setup() override;
    void update() override;
    void draw() override;
};

#endif
