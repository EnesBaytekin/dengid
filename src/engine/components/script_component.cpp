#include "engine/components/script_component.hpp"

void ScriptComponent::accept_visitor(IComponentVisitor& visitor) {
    visitor.visit_script_component(*this);
}

void ScriptComponent::init(Object& object) {
    if (script) {
        script->init(object);
    }
}

void ScriptComponent::draw(Object& object) {
    if (script) {
        script->draw(object);
    }
}

void ScriptComponent::update(Object& object) {
    if (script) {
        script->update(object);
    }
}
