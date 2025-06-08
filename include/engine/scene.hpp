#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include "engine/object.hpp"

class Scene {
protected:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Object>> objects_to_spawn;
public:
    Scene() = default;
    ~Scene() = default;

    void draw();
    void update();

    void spawn_object(std::shared_ptr<Object> object) { objects_to_spawn.push_back(object); }
    void delete_object(std::shared_ptr<Object> object) {
        auto it = std::remove(objects.begin(), objects.end(), object);
        if (it != objects.end()) {
            objects.erase(it, objects.end());
        }
    }
    std::vector<std::shared_ptr<Object>>& get_objects() { return objects; }
    std::vector<std::shared_ptr<Object>> get_objects_with_name(const std::string& name) {
        std::vector<std::shared_ptr<Object>> filtered_objects;
        for (const auto& object : objects) {
            if (object->name == name) {
                filtered_objects.push_back(object);
            }
        }
        return filtered_objects;
    }
    std::shared_ptr<Object> get_object_by_name(const std::string& name) {
        for (const auto& object : objects) {
            if (object->name == name) {
                return object;
            }
        }
        return nullptr;
    }
};

#endif
