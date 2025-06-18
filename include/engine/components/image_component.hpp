#ifndef IMAGE_COMPONENT_HPP
#define IMAGE_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "image/image.hpp"
#include <string>
#include "math/vector2.hpp"
#include "app/app_main.hpp"
#include "image/image_resource.hpp"

class ImageComponent: public IComponent {
private:
    std::string image_id;
    Vector2 scale = {1.0f, 1.0f};
    bool flip_x = false;
    bool flip_y = false;

    int frame_count = 1;
    int frame = 0;
    float animation_speed = 1.0f;
    bool is_animated = false;
    bool loop = true;

    bool visible = true;

    double start_at = 0.0;
public:
    ImageComponent(std::string _image_id)
        : IComponent(ComponentType::IMAGE_COMPONENT)
        , image_id(_image_id) {}
    ~ImageComponent() override = default;

    void accept_visitor(IComponentVisitor& visitor) override;

    void init(Object& object) override;
    void draw(Object& object) override;
    void update(Object& object) override;
    void        set_image_id(std::string id) { image_id = id; }
    std::string get_image_id() { return image_id; }
    Vector2     get_size() { auto image = ImageResource::get_instance().get_image(image_id); return {(float)image->get_width()*scale.x/frame_count, (float)image->get_height()*scale.y}; }
    void        set_scale(Vector2 _scale) { scale = _scale; }
    Vector2     get_scale() { return scale; }
    void        set_flip_x(bool _flip_x) { flip_x = _flip_x; }
    bool        get_flip_x() { return flip_x; }
    void        set_flip_y(bool _flip_y) { flip_y = _flip_y; }
    bool        get_flip_y() { return flip_y; }
    void        set_frame_count(int count) { frame_count = (count > 0) ? (count) : (1);
                                             if (frame >= frame_count) frame = frame_count-1; }
    int         get_frame_count() { return frame_count; }
    void        set_frame(int index) { frame = (index >= frame_count) ? (frame_count-1) : ((index < 0) ? (0) : (index)); }
    int         get_frame() { return frame; }
    void        set_animation_speed(float speed) { animation_speed = speed; }
    float       get_animation_speed() { return animation_speed; }
    void        set_is_animated(bool _is_animated) { is_animated = _is_animated; }
    bool        get_is_animated() { return is_animated; }
    void        set_visible(bool _visible) { visible = _visible; }
    bool        get_visible() { return visible; }

    void start_animation() { start_at = AppMain::get_instance().get_now(); };

    void start_new_animation(std::string new_image_id, int new_frame_count=-1, float new_animation_speed=-1.0f, int new_flip_x=-1, int new_flip_y=-1, int new_is_animated=-1, int new_loop=-1, bool force_start=false) {
        if (image_id != new_image_id || force_start) {
            image_id = new_image_id;
            frame = 0;
            if (new_frame_count != -1) {
                frame_count = new_frame_count;
            }
            if (new_animation_speed != -1.0f) {
                animation_speed = new_animation_speed;
            }
            if (new_flip_x != -1) {
                flip_x = new_flip_x;
            }
            if (new_flip_y != -1) {
                flip_y = new_flip_y;
            }
            if (new_is_animated != -1) {
                is_animated = new_is_animated;
            }
            if (new_loop != -1) {
                loop = new_loop;
            }
            start_animation();
        }
    }
};

#endif