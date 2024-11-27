#ifndef I_APP_IMPLEMENTATION_HPP
#define I_APP_IMPLEMENTATION_HPP

#include <string>

class IAppImplementation {
protected:
    std::string window_name;
    int window_width;
    int window_height;
public:
    IAppImplementation(std::string name, int width, int height):
        window_name(name),
        window_width(width),
        window_height(height) {}
    virtual ~IAppImplementation() = default;
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void create_frame() = 0;
    virtual void clear_renderer() = 0;
    virtual void render() = 0;

    virtual void draw_rect(int x, int y, int width, int height) = 0;
};

#endif
