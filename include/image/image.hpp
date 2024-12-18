#ifndef IMAGE_HPP
#define IMAGE_HPP

class Image {
protected:
    int width;
    int height;
public:
    virtual ~Image() = default;
    virtual void* get_native_image() = 0;
    
    int get_width() { return width; }
    int get_height() { return height; }
};

#endif
