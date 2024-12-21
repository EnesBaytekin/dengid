#include "engine/components/script_component.hpp"

void ScriptComponent::accept_visitor(IComponentVisitor& visitor) {
    visitor.visit_script_component(*this);
}

void ScriptComponent::draw(Object& object) {
    
}

void ScriptComponent::update(Object& object) {
    
}
