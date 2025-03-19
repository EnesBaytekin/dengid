#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "engine/components/script.hpp"
#include <string>
#include <memory>

class ScriptComponent: public IComponent {
private:
    std::string script_file_name;
    std::unique_ptr<Script> script;
public:
    ScriptComponent(std::string file_name)
        : IComponent(ComponentType::SCRIPT_COMPONENT)
        , script_file_name(file_name)
        {
            size_t last_dot = file_name.find_last_of(".");
            if (last_dot != std::string::npos) {
                file_name = file_name.substr(0, last_dot);
            }
            script = std::move(ScriptFactory::create_script(file_name));
        }
    ~ScriptComponent() override = default;

    void accept_visitor(IComponentVisitor& visitor) override;

    void init(Object& object) override;
    void draw(Object& object) override;
    void update(Object& object) override;
    void        set_script_file_name(std::string file_name) { script_file_name = file_name; }
    std::string get_script_file_name() { return script_file_name; }
    void                     set_script(std::unique_ptr<Script> _script) { script = std::move(_script); }
    std::unique_ptr<Script>& get_script() { return script; }
};

#endif
