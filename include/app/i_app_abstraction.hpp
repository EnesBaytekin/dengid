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
    void draw_image(const std::shared_ptr<Image> image, int x, int y)       { implementation->draw_image(image, x, y); }
    void draw_imgui_image(const std::shared_ptr<Image> image, int width=0, int height=0) { implementation->draw_imgui_image(image, width, height); }
};

#endif
