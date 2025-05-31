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
#include "engine/camera.hpp"

class Scene;

class AppMain: public IAppAbstraction {
private:
    EnumAppViewType current_view_type;
    std::map<EnumAppViewType, std::shared_ptr<AppView>> views;
    std::shared_ptr<Scene> main_scene;
    
    std::unique_ptr<Camera> camera;

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
        Vector2 camera_position = Vector2(-320, -20);
        camera = std::make_unique<Camera>(camera_position);
        initialize_imgui_style();
    }

    void                        add_view(const EnumAppViewType& type, std::shared_ptr<AppView> view) { views.insert({type, view}); }
    void                        set_view(const EnumAppViewType& type) { current_view_type = type; }
    std::shared_ptr<AppView>    get_view() { return views[current_view_type]; }
    EnumAppViewType             get_current_view_type() { return current_view_type; }
    void                        set_main_scene(std::shared_ptr<Scene> scene) { main_scene = scene; }
    std::shared_ptr<Scene>      get_main_scene() { return main_scene; }
    void                        set_camera(std::unique_ptr<Camera> cam) { camera = std::move(cam); }
    std::unique_ptr<Camera>&    get_camera() { return camera; }

    void setup() override;
    void update() override;
    void draw() override;
    void draw_rect(int x, int y, int width, int height, int r, int g, int b, int a) override {
        Vector2 draw_position = Vector2(x, y);
        if (camera) {
            draw_position -= camera->get_position();
        }
        implementation->draw_rect(draw_position.x, draw_position.y, width, height, r, g, b, a);
    }
    void draw_image(const std::string& image_id, int x, int y,
                     float scale_x=1, float scale_y=1, bool flip_x=false, bool flip_y=false,
                     int src_x=0, int src_y=0, int src_w=0, int src_h=0) override
    {
        Vector2 draw_position = Vector2(x, y);
        if (camera) {
            draw_position -= camera->get_position();
        }
        implementation->draw_image(image_id, draw_position.x, draw_position.y, scale_x, scale_y, flip_x, flip_y, src_x, src_y, src_w, src_h);
    }

    Vector2 get_mouse_position_on_scene() {
        Vector2 mouse_position = get_mouse_position();
        if (camera) {
            mouse_position += camera->get_position();
        }
        return mouse_position;
    }
    void print(std::string message) {
        if (get_current_view_type() == EnumAppViewType::PROJECT_VIEW) {
            ((ImguiWindowTerminal*)(get_view()->get_window("terminal").get()))->print(message);
        }
    }
};

#endif
