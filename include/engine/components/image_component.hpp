#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "image/image.hpp"
#include <string>

class ImageComponent: public IComponent {
private:
    std::string image_id;
public:
    ImageComponent(std::string _image_id)
        : IComponent()
        , image_id(_image_id) {}
    ~ImageComponent() override = default;

    void accept_visitor(ComponentVisitor& visitor) override;

    ComponentType get_type() override { return ComponentType::IMAGE; }
    void draw(Object& object) override;
    void update(Object& object) override;
    std::string get_image_id() { return image_id; }
};

#endif
