#pragma once
#include <filesystem>
#include <map>

class Texture;

class TextureManager {
public:
    Texture* Load(const std::filesystem::path& filePath);
    void Unload();

private:
    std::map<std::filesystem::path, Texture*> pathToTexture;
};