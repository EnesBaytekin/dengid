#ifndef HITBOX_COMPONENT_HPP
#define HITBOX_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "image/image.hpp"
#include <string>
#include "math/vector2.hpp"
#include "app/app_main.hpp"
#include "image/image_resource.hpp"
#include "math/rect.hpp"

class HitboxComponent: public IComponent {
private:
    Vector2 position;
    Vector2 offset;
    Vector2 size;
public:
    HitboxComponent(float x, float y, float w, float h)
        : IComponent(ComponentType::HITBOX_COMPONENT)
        , offset(x, y)
        , size(w, h) {}
    ~HitboxComponent() override = default;

    void accept_visitor(IComponentVisitor& visitor) override;

    void init(Object& object) override;
    void draw(Object& object) override;
    void update(Object& object) override;
    
    void    set_position(Vector2 new_position) { position = new_position; }
    Vector2 get_position() { return position; }
    void    set_offset(Vector2 new_offset) { offset = new_offset; }
    Vector2 get_offset() { return offset; }
    void    set_size(Vector2 new_size) { size = new_size; }
    Vector2 get_size() { return size; }
    Rect    get_dynamic_rect() { return Rect(position+offset, size); }
    Rect    get_static_rect() { return Rect(offset, size); }
    Rect    get_rect_at(Vector2 position) { return Rect(position+offset, size); }
    bool    is_colliding(HitboxComponent& other) { return get_dynamic_rect().is_colliding(other.get_dynamic_rect()); }
};

#endif
