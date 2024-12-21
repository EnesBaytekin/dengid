#ifndef COMPONENT_SAVE_VISITOR_HPP
#define COMPONENT_SAVE_VISITOR_HPP

#include "engine/components/i_component_visitor.hpp"
#include <string>

class ImageComponent;

class ComponentSaveVisitor: public IComponentVisitor {
private:
    std::string components_data;
public:
    ComponentSaveVisitor() = default;
    ~ComponentSaveVisitor() = default;

    void visit_image_component(ImageComponent& component) override;
    void visit_script_component(ScriptComponent& component) override;

    std::string get_components_data() { return components_data; }
};

#endif