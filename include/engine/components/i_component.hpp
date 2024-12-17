#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include "engine/components/component_type.hpp"

class Object;
class ComponentVisitor;

class IComponent {
public:
    IComponent() = default;
    virtual ~IComponent() = default;

    virtual ComponentType get_type() = 0;
    virtual void draw(Object& object) = 0;
    virtual void update(Object& object) = 0;

    virtual void accept_visitor(ComponentVisitor& visitor) = 0;
};

#endif
