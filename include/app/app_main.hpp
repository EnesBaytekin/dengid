#ifndef APP_MAIN_HPP
#define APP_MAIN_HPP

#include "app/i_app_abstraction.hpp"
#include "app_views/enum_app_view_type.hpp"
#include <filesystem>
#include <map>
#include "project/project_settings.hpp"
#include "app/initialize_imgui_style.hpp"
#include "imgui_windows/imgui_window_terminal.hpp"
#include "app_views/app_view.hpp"

class Scene;

class AppMain: public IAppAbstraction {
private:
    EnumAppViewType current_view_type;
    std::map<EnumAppViewType, std::shared_ptr<AppView>> views;
    std::shared_ptr<Scene> main_scene;

    AppMain(): current_view_type(EnumAppViewType::INITIAL_VIEW) {}
    ~AppMain() = default;
public:
    AppMain(const AppMain&) = delete;
    AppMain& operator=(const AppMain&) = delete;

    static AppMain& get_instance() {
        static AppMain instance;
        return instance;
    }
    void initialize(IAppImplementation* _implementation) {
        IAppAbstraction::initialize(_implementation);
        initialize_imgui_style();
    }

    void                        add_view(const EnumAppViewType& type, std::shared_ptr<AppView> view) { views.insert({type, view}); }
    void                        set_view(const EnumAppViewType& type) { current_view_type = type; }
    std::shared_ptr<AppView>    get_view() { return views[current_view_type]; }
    EnumAppViewType             get_current_view_type() { return current_view_type; }
    void                        set_main_scene(std::shared_ptr<Scene> scene) { main_scene = scene; }
    std::shared_ptr<Scene>      get_main_scene() { return main_scene; }

    void setup() override;
    void update() override;
    void draw() override;
    
    void print(std::string message, bool add_new_line=true) override {
        if (get_current_view_type() == EnumAppViewType::PROJECT_VIEW) {
            if (add_new_line) {
                message += "\n";
            }
            ((ImguiWindowTerminal*)(get_view()->get_window("terminal").get()))->print(message);
        }
    }
};

#endif
