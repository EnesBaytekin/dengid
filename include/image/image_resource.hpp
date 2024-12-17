#ifndef IMAGE_RESOURCE_HPP
#define IMAGE_RESOURCE_HPP

#include <map>
#include <string>
#include <memory>

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

    void                    add_image(const std::string& id, std::shared_ptr<Image> image) { images[id] = image; }
    bool                    has_image(const std::string& id) { return images.find(id) != images.end(); }
    std::shared_ptr<Image>  get_image(const std::string& id) { return images[id]; }
};

#endif
