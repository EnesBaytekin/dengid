#include "engine/components/image_component.hpp"
#include "app/app_main.hpp"
#include "engine/object.hpp"

void ImageComponent::draw(Object& object) {
    AppMain& app = AppMain::get_instance();
    app.draw_image(image, object.position.x, object.position.y);
}

void ImageComponent::update(Object& object) {

}
