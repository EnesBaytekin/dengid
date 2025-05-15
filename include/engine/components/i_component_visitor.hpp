#ifndef ICOMPONENT_VISITOR_HPP
#define ICOMPONENT_VISITOR_HPP

class ImageComponent;
class ScriptComponent;
class HitboxComponent;
class YSortComponent;

class IComponentVisitor {
public:
    IComponentVisitor() = default;
    virtual ~IComponentVisitor() = default;

    virtual void visit_image_component(ImageComponent& component) = 0;
    virtual void visit_script_component(ScriptComponent& component) = 0;
    virtual void visit_hitbox_component(HitboxComponent& component) = 0;
    virtual void visit_ysort_component(YSortComponent& component) = 0;
};

#endif