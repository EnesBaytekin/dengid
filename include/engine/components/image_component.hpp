#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "image/image.hpp"
#include <string>

class ImageComponent: public IComponent {
private:
    std::string image_id;
    float scale = 1;
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
    void        set_scale(float _scale) { scale = _scale; }
    float       get_scale() { return scale; }
};

#endif
