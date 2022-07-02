#include "Engine.h"
#include "Texture.h"
#include "TextureManager.h"

using namespace coconut;

Texture* TextureManager::Load(const char* filePath)
{
    if (pathToTexture.find(filePath) == pathToTexture.end())
    {
        pathToTexture[filePath] = new Texture(filePath);
    }
    return pathToTexture[filePath];
}

void TextureManager::Unload() {
	Engine::GetLogger().LogEvent(Part::Entire, "Clear Textures");
    for (std::pair<const char*, Texture*> pathTexturePair : pathToTexture) {
        delete pathTexturePair.second;
    }
    pathToTexture.clear();
}