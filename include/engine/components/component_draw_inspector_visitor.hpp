#ifndef COMPONENT_DRAW_INSPECTOR_VISITOR_HPP
#define COMPONENT_DRAW_INSPECTOR_VISITOR_HPP

#include "engine/components/i_component_visitor.hpp"

class ImageComponent;

class ComponentDrawInspectorVisitor: public IComponentVisitor {
public:
    ComponentDrawInspectorVisitor() = default;
    ~ComponentDrawInspectorVisitor() = default;

    void visit_image_component(ImageComponent& component) override;
};

#endif