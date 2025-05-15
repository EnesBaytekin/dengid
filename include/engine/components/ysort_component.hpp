#ifndef YSORT_COMPONENT_HPP
#define YSORT_COMPONENT_HPP

#include "engine/components/i_component.hpp"
#include "engine/components/i_component_visitor.hpp"
#include "image/image.hpp"
#include <string>
#include "math/vector2.hpp"
#include "app/app_main.hpp"
#include "image/image_resource.hpp"
#include "math/rect.hpp"

class YSortComponent: public IComponent {
public:
    YSortComponent(): IComponent(ComponentType::YSORT_COMPONENT) {}
    ~YSortComponent() override = default;

    void accept_visitor(IComponentVisitor& visitor) override;

    void init(Object& object) override;
    void draw(Object& object) override;
    void update(Object& object) override;
};

#endif
