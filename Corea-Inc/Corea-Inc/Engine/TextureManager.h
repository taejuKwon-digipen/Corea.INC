#pragma once
#include <filesystem>
#include <map>

namespace coconut
{
    class Texture;
	
    class TextureManager
    {
    public:
        Texture* Load(const char* filePath);
        void Unload();

    private:
        std::map<const char*, Texture*> pathToTexture;
    };
}