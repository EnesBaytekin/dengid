#ifndef COMPONENT_SAVE_VISITOR_HPP
#define COMPONENT_SAVE_VISITOR_HPP

#include "engine/components/i_component_visitor.hpp"
#include <string>
#include "json.hpp"

using json = nlohmann::ordered_json;

class ImageComponent;

class ComponentSaveVisitor: public IComponentVisitor {
private:
    json components_data;
public:
    ComponentSaveVisitor() = default;
    ~ComponentSaveVisitor() = default;

    void visit_image_component(ImageComponent& component) override;
    void visit_script_component(ScriptComponent& component) override;
    void visit_hitbox_component(HitboxComponent& component) override;

    json get_components_data() { return components_data; }
};

#endif