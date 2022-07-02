#pragma once
#include <string>
#include "Vec2.h"

class Window {
public:
    void Init(std::string windowName);
    void Resize(int newWidth, int newHeight);
    math::ivec2 GetSize();
    void Clear(unsigned int color);
    void Update();
private:
    math::ivec2 windowSize;
};
