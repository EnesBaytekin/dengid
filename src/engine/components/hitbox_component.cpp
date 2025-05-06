#include "engine/components/hitbox_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "engine/object.hpp"
#include "imgui.h"
#include "imgui_windows/imgui_window_inspector.hpp"
#include "engine/editor_utility.hpp"

void HitboxComponent::init(Object& object) {

}

void HitboxComponent::draw(Object& object) {

}

void HitboxComponent::update(Object& object) {
    position = object.position;
}

void HitboxComponent::accept_visitor(IComponentVisitor& visitor) {
    visitor.visit_hitbox_component(*this);
}
