#include "engine/object.hpp"

void Object::init() {
    for (auto& component : components) {
        component->init(*this);
    }
}

void Object::draw() {
#ifdef BUILD_MODE__ENGINE
    if (!has_component(ComponentType::IMAGE_COMPONENT)) {
        AppMain& app = AppMain::get_instance();
        app.draw_rect(position.x-2, position.y, 5, 1, 255, 255, 255, 192);
        app.draw_rect(position.x, position.y-2, 1, 5, 255, 255, 255, 192);
    }
#endif
    for (auto& component : components) {
        component->draw(*this);
    }
}

void Object::update() {
    for (auto& component : components) {
        component->update(*this);
    }
}
