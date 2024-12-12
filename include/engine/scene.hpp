#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>

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
    std::vector<std::shared_ptr<Object>> get_objects() { return objects; }
};

#endif
