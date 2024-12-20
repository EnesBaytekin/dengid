#ifndef I_APP_ABSTRACTION_HPP
#define I_APP_ABSTRACTION_HPP

#include "app/i_app_implementation.hpp"
#include "image/image.hpp"

class IAppAbstraction {
protected:
    IAppImplementation* implementation;
    bool running;

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
    void run() {
        running = true;
        implementation->setup();
        setup();
        while (running) {
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
    }

    void draw_rect(int x, int y, int width, int height)     { implementation->draw_rect(x, y, width, height); }
    std::shared_ptr<Image> load_image(const std::string& file_path)         { return implementation->load_image(file_path); }
    void draw_image(const std::string& image_id , int x, int y,
                    float scale_x=1, float scale_y=1, bool flip_x=false, bool flip_y=false,
                    int src_x=0, int src_y=0, int src_w=0, int src_h=0)
        { implementation->draw_image(image_id, x, y,
                                     scale_x, scale_y, flip_x, flip_y,
                                     src_x, src_y, src_w, src_h); }
    void draw_imgui_image(const std::string& image_id, int width=0, int height=0) { implementation->draw_imgui_image(image_id, width, height); }
};

#endif
