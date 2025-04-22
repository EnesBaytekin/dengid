#pragma once

#include "math/rect.hpp"
#include "object.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/hitbox_component.hpp"
#include "engine/components/component_type.hpp"

class EditorUtility {
public:
    static std::unique_ptr<Rect> get_object_rect(std::shared_ptr<Object>& object) {
        if (!object) {
            return std::make_unique<Rect>(0, 0, 0, 0);
        }
        if (object->has_component(ComponentType::HITBOX_COMPONENT)) {
            auto& hitbox_component = *dynamic_cast<HitboxComponent*>(object->get_component(ComponentType::HITBOX_COMPONENT).get());
            return std::make_unique<Rect>(hitbox_component.get_rect_at(object->position));
        } else if (object->has_component(ComponentType::IMAGE_COMPONENT)) {
            auto& image_component = *dynamic_cast<ImageComponent*>(object->get_component(ComponentType::IMAGE_COMPONENT).get());
            return std::make_unique<Rect>(object->position, image_component.get_size());
        } else {
            return std::make_unique<Rect>(object->position, 32, 32);
        }
    }
};
