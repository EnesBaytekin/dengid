#include "engine/components/ysort_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "engine/object.hpp"
#include "imgui.h"
#include "imgui_windows/imgui_window_inspector.hpp"
#include "engine/editor_utility.hpp"

void YSortComponent::init(Object& object) {

}

void YSortComponent::draw(Object& object) {

}

void YSortComponent::update(Object& object) {
    object.depth = object.position.y;
}

void YSortComponent::accept_visitor(IComponentVisitor& visitor) {
    
}
