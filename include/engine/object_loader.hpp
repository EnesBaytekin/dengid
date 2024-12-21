#ifndef OBJECT_LOADER_HPP
#define OBJECT_LOADER_HPP

#include "engine/object.hpp"
#include <string>
#include <memory>
#include <deque>

class ImageComponent;
class ScriptComponent;

class ObjectLoader {
private:
    std::deque<std::string> object_data;

    std::unique_ptr<ImageComponent> load_image_component();
    std::unique_ptr<ScriptComponent> load_script_component();
public:
    ObjectLoader(const std::string& raw_data);
    ~ObjectLoader() = default;

    std::shared_ptr<Object> load_object();
};


#endif