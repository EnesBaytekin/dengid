#ifndef I_APP_ABSTRACTION_HPP
#define I_APP_ABSTRACTION_HPP

#include <imgui.h>
#include "app/i_app_implementation.hpp"
#include "image/image.hpp"
#include "math/vector2.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include "project/project_manager.hpp"

class IAppAbstraction {
protected:
    IAppImplementation* implementation;
    bool running;

    std::vector<SDL_Event> event_list;

    double now = 0.0;
    double delta_time = 0.0;
    Uint8 key_states[SDL_NUM_SCANCODES] = {0};
    Uint8 last_key_states[SDL_NUM_SCANCODES] = {0};

    Uint32 mouse_buttons = 0;
    Uint32 last_mouse_buttons = 0;
    Vector2 mouse_position = {0, 0};
    Vector2 last_mouse_position = {0, 0};

    int mouse_wheel_y = 0;
    int last_mouse_wheel_y = 0;

    IAppAbstraction(): running(false) {};
public:
    SDL_Window* window;

    ~IAppAbstraction() = default;
    virtual void initialize(IAppImplementation* _implementation) {
        implementation = _implementation;
        window = implementation->get_window();
    }

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void print(std::string message) { };

    void run() {
        running = true;
        implementation->setup();
        setup();
        while (running) {
            double last_now = now;
            now = SDL_GetTicks()/1000.0;
            double frame_duration = now-last_now;
            if (frame_duration < 0.016) {
                SDL_Delay((0.016-frame_duration)*1000);
                now = SDL_GetTicks()/1000.0;
                frame_duration = now-last_now;
            }
            delta_time = frame_duration;

            const Uint8* new_key_states = SDL_GetKeyboardState(nullptr);
            if (new_key_states != nullptr) {
                memcpy(last_key_states, key_states, SDL_NUM_SCANCODES);
                memcpy(key_states, new_key_states, SDL_NUM_SCANCODES);
            }

            last_mouse_buttons = mouse_buttons;
            last_mouse_position = mouse_position;
            last_mouse_wheel_y = mouse_wheel_y;

            int mouse_x, mouse_y;
            mouse_buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
            mouse_position.x = mouse_x;
            mouse_position.y = mouse_y;

            mouse_wheel_y = 0;

            event_list.clear();
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                event_list.push_back(event);
                if (event.type == SDL_MOUSEWHEEL) {
                    mouse_wheel_y += event.wheel.y;
                }
            }

            implementation->update();
            implementation->create_frame();
            update();
            implementation->clear_renderer();
            draw();
            implementation->render();
        }
    }
    void quit() {
        running = false;
        auto& project_manager = ProjectManager::get_instance();
        project_manager.stop_game();
    }

    double get_now() { return now; }
    double get_delta_time() { return delta_time; }

    virtual void draw_rect(int x, int y, int width, int height, int r, int g, int b, int a, bool fill=true) { implementation->draw_rect(x, y, width, height, r, g, b, a, fill); }
    std::shared_ptr<Image> load_image(const std::string& file_path)         { return implementation->load_image(file_path); }
    virtual void draw_image(const std::string& image_id , int x, int y,
                    float scale_x=1, float scale_y=1, bool flip_x=false, bool flip_y=false,
                    int src_x=0, int src_y=0, int src_w=0, int src_h=0)
        { implementation->draw_image(image_id, x, y,
                                     scale_x, scale_y, flip_x, flip_y,
                                     src_x, src_y, src_w, src_h); }
    void draw_imgui_image(const std::string& image_id, int width=0, int height=0) { implementation->draw_imgui_image(image_id, width, height); }
    bool is_key_pressed(SDL_Scancode key) { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureKeyboard && key_states[key]; 
    }
    bool is_key_just_pressed(SDL_Scancode key) { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureKeyboard && key_states[key] && !last_key_states[key]; 
    }
    bool is_key_just_released(SDL_Scancode key) { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureKeyboard && !key_states[key] && last_key_states[key]; 
    }

    Vector2 get_mouse_position() { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureMouse ? mouse_position : Vector2{0, 0}; 
    }
    Vector2 get_mouse_motion() { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureMouse ? mouse_position - last_mouse_position : Vector2{0, 0}; 
    }
    bool is_mouse_button_pressed(Uint32 button) { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureMouse && (mouse_buttons & SDL_BUTTON(button)); 
    }
    bool is_mouse_button_just_pressed(Uint32 button) { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureMouse && (mouse_buttons & SDL_BUTTON(button)) && !(last_mouse_buttons & SDL_BUTTON(button)); 
    }
    bool is_mouse_button_just_released(Uint32 button) { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureMouse && !(mouse_buttons & SDL_BUTTON(button)) && (last_mouse_buttons & SDL_BUTTON(button)); 
    }

    int get_mouse_wheel() { 
        ImGuiIO& io = ImGui::GetIO();
        return !io.WantCaptureMouse ? mouse_wheel_y : 0; 
    }
    bool is_mouse_wheel_scrolled_up() { 
        return get_mouse_wheel() > 0; 
    }
    bool is_mouse_wheel_scrolled_down() { 
        return get_mouse_wheel() < 0; 
    }
};

#endif
