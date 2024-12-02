#ifndef IMAGE_HPP
#define IMAGE_HPP

class Image {
public:
    virtual ~Image() = default;
    virtual void* get_native_image() = 0;
};

#endif
