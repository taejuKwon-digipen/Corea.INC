//Jihyeon Song

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"

class Background : public Component {
public:
    void Add(const std::filesystem::path& texturePath);
    void Draw();
    void Unload();
    math::ivec2 Size();

private:
    struct ParallaxInfo {
        Texture* backimage;
    };
    std::vector<ParallaxInfo> backgrounds;
};