#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include "engine/components/component_type.hpp"

class Object;
class IComponentVisitor;

class IComponent {
private:
    ComponentType type;
public:
    IComponent(ComponentType _type): type(_type) {}
    virtual ~IComponent() = default;

    virtual void draw(Object& object) = 0;
    virtual void update(Object& object) = 0;

    ComponentType get_type() { return type;};

    virtual void accept_visitor(IComponentVisitor& visitor) = 0;
};

#endif
