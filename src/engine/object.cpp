#include "engine/object.hpp"

void Object::draw() {
    for (auto& component : components) {
        component->draw(*this);
    }
}

void Object::update() {
    for (auto& component : components) {
        component->update(*this);
    }
}
