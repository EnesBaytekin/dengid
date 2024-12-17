#ifndef ICOMPONENT_VISITOR_HPP
#define ICOMPONENT_VISITOR_HPP

class ImageComponent;

class IComponentVisitor {
public:
    IComponentVisitor() = default;
    virtual ~IComponentVisitor() = default;

    virtual void visit_image_component(ImageComponent& component) = 0;
};

#endif