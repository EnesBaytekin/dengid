#ifndef COMPONENT_VISITOR_HPP
#define COMPONENT_VISITOR_HPP

class ImageComponent;

class ComponentVisitor {
public:
    ComponentVisitor() = default;
    ~ComponentVisitor() = default;

    void visit_image_component(ImageComponent& component);
};

#endif