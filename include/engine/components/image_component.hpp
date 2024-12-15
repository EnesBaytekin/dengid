#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "image/image.hpp"
#include <memory>

class ImageComponent: public IComponent {
private:
    std::shared_ptr<Image> image;
public:
    ImageComponent(std::shared_ptr<Image> _image)
        : IComponent()
        , image(_image) {}
    ~ImageComponent() override = default;

    void draw(Object& object) override;
    void update(Object& object) override;
};

#endif
