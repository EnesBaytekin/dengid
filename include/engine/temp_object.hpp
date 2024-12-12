#ifndef TEMP_OBJECT_HPP
#define TEMP_OBJECT_HPP

#include "engine/object.hpp"

class TempObject : public Object {
public:
    TempObject() = default;
    ~TempObject() = default;
    void draw();
    void update();
};

#endif
