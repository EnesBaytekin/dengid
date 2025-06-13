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
    auto new_objects = objects_to_spawn;
    objects.insert(objects.end(), objects_to_spawn.begin(), objects_to_spawn.end());
    objects_to_spawn.clear();
    for (auto& object : new_objects) {
        object->init();
    }
}

void Scene::draw() {
    std::vector<std::shared_ptr<Object>> sorted_objects = objects;
    std::sort(sorted_objects.begin(), sorted_objects.end(), [](const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b) {
        return a->depth < b->depth;
    });
    for (auto& object : sorted_objects) {
        object->draw();
    }
}
