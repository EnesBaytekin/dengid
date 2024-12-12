#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

class Object;

class Scene {
protected:
    std::vector<Object> objects;
public:
    Scene() = default;
    ~Scene() = default;

    void draw();
    void update();

    void spawn_object(Object& object) { objects.push_back(object); }
    std::vector<Object> get_objects() { return objects; }
};

#endif
