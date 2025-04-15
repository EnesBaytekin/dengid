#include "engine/object.hpp"

void Object::draw() {
    if (!has_component(ComponentType::IMAGE_COMPONENT)) {
        AppMain& app = AppMain::get_instance();
        app.draw_rect(position.x, position.y, 32, 32);
    }
    for (auto& component : components) {
        component->draw(*this);
    }
}

void Object::update() {
    for (auto& component : components) {
        component->update(*this);
    }
}
