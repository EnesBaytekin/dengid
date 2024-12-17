#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <utility>

class Object;
class IComponentVisitor;

class IComponent {
public:
    IComponent() = default;
    virtual ~IComponent() = default;

    virtual void draw(Object& object) = 0;
    virtual void update(Object& object) = 0;

    virtual void accept_visitor(IComponentVisitor& visitor) = 0;
};

#endif
