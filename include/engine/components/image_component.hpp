#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "image/image.hpp"
#include <string>
#include <math/vector2.hpp>

class ImageComponent: public IComponent {
private:
    std::string image_id;
    Vector2 scale = {1.0f, 1.0f};
    bool flip_x = false;
    bool flip_y = false;
public:
    ImageComponent(std::string _image_id)
        : IComponent()
        , image_id(_image_id) {}
    ~ImageComponent() override = default;

    void accept_visitor(IComponentVisitor& visitor) override;

    void draw(Object& object) override;
    void update(Object& object) override;
    void        set_image_id(std::string id) { image_id = id; }
    std::string get_image_id() { return image_id; }
    void        set_scale(Vector2 _scale) { scale = _scale; }
    Vector2     get_scale() { return scale; }
    void        set_flip_x(bool _flip_x) { flip_x = _flip_x; }
    bool        get_flip_x() { return flip_x; }
    void        set_flip_y(bool _flip_y) { flip_y = _flip_y; }
    bool        get_flip_y() { return flip_y; }
};

#endif
