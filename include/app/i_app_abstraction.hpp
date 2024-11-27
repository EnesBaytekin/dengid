#ifndef I_APP_ABSTRACTION_HPP
#define I_APP_ABSTRACTION_HPP

#include "app/i_app_implementation.hpp"

class IAppAbstraction {
protected:
    IAppImplementation* implementation;
    bool running;
public:
    IAppAbstraction(IAppImplementation* _implementation):
        implementation(_implementation),
        running(false) {};
    ~IAppAbstraction() = default;
    virtual void setup() = 0;
    virtual void check_events() = 0;
    virtual void update() = 0;
    void run() {
        running = true;
        implementation->setup();
        setup();
        while (running) {
            check_events();
            implementation->update();
            implementation->create_frame();
            update();
            implementation->render();
        }
    }
    void quit() {
        running = false;
    }

    void draw_rect(int x, int y, int width, int height) {
        implementation->draw_rect(x, y, width, height);
    }
};

#endif
