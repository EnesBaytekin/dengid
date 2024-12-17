#ifndef IMAGE_RESOURCE_HPP
#define IMAGE_RESOURCE_HPP

#include <map>
#include <string>
#include <memory>
#include "app/app_main.hpp"
#include "project/project_manager.hpp"

class Image;

class ImageResource {
private:
    std::map<std::string, std::shared_ptr<Image>> images;

    ImageResource() = default;
    ~ImageResource() = default;
public:
    ImageResource(const ImageResource&) = delete;
    ImageResource& operator=(const ImageResource&) = delete;
    
    static ImageResource& get_instance() {
        static ImageResource instance;
        return instance;
    }

    std::shared_ptr<Image>  get_image(const std::string& id) {
        auto it = images.find(id);
        if (it == images.end()) {
            AppMain& app = AppMain::get_instance();
            ProjectManager& project_manager = ProjectManager::get_instance();
            auto image = app.load_image(project_manager.get_project_path()/id);
            images[id] = image;
            return image;
        } else {
            return it->second;
        }
    }
};

#endif
