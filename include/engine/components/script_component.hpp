#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include <string>

class ScriptComponent: public IComponent {
private:
    std::string script_file_name;
public:
    ScriptComponent(std::string file_name)
        : IComponent(ComponentType::SCRIPT_COMPONENT)
        , script_file_name(file_name) {}
    ~ScriptComponent() override = default;

    void accept_visitor(IComponentVisitor& visitor) override;

    void draw(Object& object) override;
    void update(Object& object) override;
    void        set_script_file_name(std::string file_name) { script_file_name = file_name; }
    std::string get_script_file_name() { return script_file_name; }
};

#endif
