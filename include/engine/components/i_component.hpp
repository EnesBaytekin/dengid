#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

class Object;

class IComponent {
public:
    IComponent() = default;
    virtual ~IComponent() = default;

    virtual void draw(Object& object) = 0;
    virtual void update(Object& object) = 0;
};

#endif
