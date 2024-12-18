#include "engine/components/image_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "app/app_main.hpp"
#include "engine/object.hpp"

void ImageComponent::draw(Object& object) {
    AppMain& app = AppMain::get_instance();
    app.draw_image(image_id, object.position.x, object.position.y, scale.x, scale.y, flip_x, flip_y);
}

void ImageComponent::update(Object& object) {

}

void ImageComponent::accept_visitor(IComponentVisitor& visitor) {
    visitor.visit_image_component(*this);
}
