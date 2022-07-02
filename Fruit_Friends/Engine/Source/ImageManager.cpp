#include "../Header/Engine.h"
#include "../Header/ImageManager.h"
#include "../Header/Image.h"

using namespace coconut;

Image* ImageManager::Load(const char* filePath) {
    if (pathToTexture.find(filePath) == pathToTexture.end()) {
        pathToTexture[filePath] = new Image(filePath);
    }
    return pathToTexture[filePath];
}

void ImageManager::Unload() {
    Engine::GetLogger().LogEvent(Part::Entire,"Clear Textures");
    for (std::pair<const char*, Image*> pathTexturePair : pathToTexture) {
        delete pathTexturePair.second;
    }
    pathToTexture.clear();
}