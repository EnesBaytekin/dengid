#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <memory>
#include <algorithm>

void Scene::update() {
    for (auto object : objects) {
        object->update();
    }
    objects.erase(std::remove_if(objects.begin(), objects.end(), [](std::shared_ptr<Object> object) {
        return object->is_dead();
    }), objects.end());
}

void Scene::draw() {
    for (auto& object : objects) {
        object->draw();
    }
}
