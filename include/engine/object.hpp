#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "math/vector2.hpp"
#include "app/app_main.hpp"
#include "engine/components/i_component.hpp"
#include <vector>
#include <algorithm>

class Object {
private:
    std::vector<std::unique_ptr<IComponent>> components;
    bool dead = false;
public:
    Vector2 position;
    int depth = 0;
    std::string name = "New Object";

    Object(Vector2 _position): position(_position) {};
    Object(float x, float y): position(Vector2(x, y)) {};
    Object(): position(Vector2(0.0f, 0.0f)) {};
    ~Object() = default;

    void add_component(std::unique_ptr<IComponent> component) {
        components.push_back(std::move(component));
    }
    std::vector<std::unique_ptr<IComponent>>& get_components() {
        return components;
    }
    std::unique_ptr<IComponent>& get_component(ComponentType type) {
        for (auto& component : components) {
            if (component->get_type() == type) {
                return component;
            }
        }
        return components[0];
    }
    bool has_component(ComponentType type) {
        for (auto& component : components) {
            if (component->get_type() == type) {
                return true;
            }
        }
        return false;
    }
    void remove_component(ComponentType type) {
        components.erase(
            std::remove_if(components.begin(), components.end(),
                [type](const std::unique_ptr<IComponent>& component) {
                    return component->get_type() == type;
                }
            ),
            components.end()
        );
    }
    void init();
    void draw();
    void update();

    void kill() {
        dead = true;
    }
    bool is_dead() {
        return dead;
    }
};

#endif
