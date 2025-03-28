#pragma once

#include "app/i_app_abstraction.hpp"
#include "app/initialize_imgui_style.hpp"

class Scene;

class AppMain: public IAppAbstraction {
private:
    std::shared_ptr<Scene> main_scene;

    AppMain() = default;
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

    void                        set_main_scene(std::shared_ptr<Scene> scene) { main_scene = scene; }
    std::shared_ptr<Scene>      get_main_scene() { return main_scene; }

    void setup() override;
    void update() override;
    void draw() override;
    
    void print(std::string message) { std::cout << message << std::endl; };
};
