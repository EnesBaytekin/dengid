#ifndef APP_MAIN_HPP
#define APP_MAIN_HPP

#include "app/i_app_abstraction.hpp"
#include <filesystem>

enum class AppViewState {
    INITIAL_VIEW,
    PROJECT_VIEW
};

class AppMain: public IAppAbstraction {
private:
    AppViewState view_state;
    std::filesystem::path project_path;
public:
    
    AppMain(IAppImplementation* _implementation):
        IAppAbstraction(_implementation),
        view_state(AppViewState::INITIAL_VIEW) {}
    ~AppMain() = default;

    void set_view_state(const AppViewState& new_state) {
        view_state = new_state;
    }
    AppViewState get_view_state() {
        return view_state;
    }
    void set_project_path(const std::filesystem::path& new_path) {
        project_path = new_path;
    }
    std::filesystem::path get_project_path() {
        return project_path;
    }

    void setup() override;
    void update() override;
    void draw() override;
};

#endif
