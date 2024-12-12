#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <memory>

void Scene::update() {
    for (auto object : objects) {
        object->update();
    }
}

void Scene::draw() {
    for (auto& object : objects) {
        object->draw();
    }
}
