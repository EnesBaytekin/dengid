#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "math/vector2.hpp"
#include "app/app_main.hpp"
#include "engine/components/i_component.hpp"
#include <vector>

class Object {
private:
    std::vector<std::unique_ptr<IComponent>> components;
public:
    Vector2 position;
    std::string name = "New Object";

    Object(Vector2 _position): position(_position) {};
    Object(float x, float y): position(Vector2(x, y)) {};
    Object(): position(Vector2::ZERO) {};
    ~Object() = default;

    void add_component(std::unique_ptr<IComponent> component) {
        components.push_back(std::move(component));
    }
    std::vector<std::unique_ptr<IComponent>>& get_components() {
        return components;
    }
    bool has_component(ComponentType type) {
        for (auto& component : components) {
            if (component->get_type() == type) {
                return true;
            }
        }
        return false;
    }
    void draw();
    void update();
};

#endif
