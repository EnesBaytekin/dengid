#include "engine/components/image_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "app/app_main.hpp"
#include "engine/object.hpp"
#include "image/image_resource.hpp"

void ImageComponent::init(Object& object) {

}

void ImageComponent::draw(Object& object) {
    AppMain& app = AppMain::get_instance();
    ImageResource& image_resource = ImageResource::get_instance();
    auto image = image_resource.get_image(image_id);
    int frame_w = image->get_width()/frame_count;
    int frame_h = image->get_height();
    int src_x = frame_w*frame;
    int src_y = 0;
    app.draw_image(image_id, object.position.x, object.position.y, scale.x, scale.y, flip_x, flip_y, src_x, src_y, frame_w, frame_h);
}

void ImageComponent::update(Object& object) {
    if (is_animated) {
        AppMain& app = AppMain::get_instance();
        double delta_time = app.get_now()-start_at;
        int delta_frame = animation_speed*delta_time;
        frame = delta_frame%frame_count;
    }
}

void ImageComponent::accept_visitor(IComponentVisitor& visitor) {
    visitor.visit_image_component(*this);
}
