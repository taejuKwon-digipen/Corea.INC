#pragma once
#include <map>

namespace coconut {
    class Image;
    class ImageManager {
    public:
        Image* Load(const char* filePath);
        void Unload();
    private:
        std::map<const char*, Image*> pathToTexture;
    };
}
