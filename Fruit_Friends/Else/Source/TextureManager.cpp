#include "../Header/Engine.h"
#include "../Header/Texture.h"
#include "../Header/TextureManager.h"

Texture* TextureManager::Load(const std::filesystem::path& filePath) {
    if (pathToTexture.find(filePath) == pathToTexture.end()) {
        pathToTexture[filePath] = new Texture(filePath);
    }
    return pathToTexture[filePath];
}

void TextureManager::Unload() {
    Engine::GetLogger().LogEvent(Part::Entire, "Clear Textures");
    for (std::pair<std::filesystem::path, Texture*> pathTexturePair : pathToTexture) {
        delete pathTexturePair.second;
    }
    pathToTexture.clear();
}