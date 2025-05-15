#ifndef COMPONENT_DRAW_INSPECTOR_VISITOR_HPP
#define COMPONENT_DRAW_INSPECTOR_VISITOR_HPP

#include "engine/components/i_component_visitor.hpp"

class ComponentDrawInspectorVisitor: public IComponentVisitor {
public:
    ComponentDrawInspectorVisitor() = default;
    ~ComponentDrawInspectorVisitor() = default;

    void visit_image_component(ImageComponent& component) override;
    void visit_script_component(ScriptComponent& component) override;
    void visit_hitbox_component(HitboxComponent& component) override;
    void visit_ysort_component(YSortComponent& component) override;
};

#endif