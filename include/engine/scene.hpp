#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <algorithm>

class Object;

class Scene {
protected:
    std::vector<std::shared_ptr<Object>> objects;
public:
    Scene() = default;
    ~Scene() = default;

    void draw();
    void update();

    void spawn_object(std::shared_ptr<Object> object) { objects.push_back(object); }
    void delete_object(std::shared_ptr<Object> object) {
        auto it = std::remove(objects.begin(), objects.end(), object);
        if (it != objects.end()) {
            objects.erase(it, objects.end());
        }
    }
    std::vector<std::shared_ptr<Object>> get_objects() { return objects; }
};

#endif
