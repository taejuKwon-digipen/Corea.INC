#include "Engine.h"
#include "ImageManager.h"
#include "Image.h"

using namespace coconut;

Image* ImageManager::Load(const char* filePath) {
    if (pathToTexture.find(filePath) == pathToTexture.end()) {
        pathToTexture[filePath] = new Image(filePath);
    }
    return pathToTexture[filePath];
}

void ImageManager::Unload() {
    for (std::pair<const char*, Image*> pathTexturePair : pathToTexture) {
        delete pathTexturePair.second;
    }
    pathToTexture.clear();
}