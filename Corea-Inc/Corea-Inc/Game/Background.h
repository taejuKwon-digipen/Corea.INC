//Jihyeon Song

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"

class Background : public coconut::Component {
public:
    void Add(const char* texturePath);
    void Draw();
    void Unload();
    glm::ivec2 Size();

private:
    struct ParallaxInfo {
        coconut::Texture* backimage;
    };
    std::vector<ParallaxInfo> backgrounds;
};