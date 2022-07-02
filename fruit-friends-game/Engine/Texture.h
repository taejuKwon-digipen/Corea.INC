#pragma once
#include "../../library/include/doodle/image.hpp"	//doodle::Image
#include "Vec2.h"

namespace math {
	class TransformMatrix;
}

class Texture {
	friend class TextureManager;
	friend class SpriteFont;
public:
	Texture() {}
	void Draw(math::TransformMatrix displayMatrix);
	void Draw(math::TransformMatrix displayMatrix, math::ivec2 frameSize);
	void Draw(math::TransformMatrix displayMatrix, math::ivec2 texelPos, math::ivec2 frameSize);
	math::ivec2 GetSize();
	unsigned int GetPixel(math::ivec2 pos);
private:
	Texture(const std::filesystem::path& filePath);
	Texture(doodle::Image&& doodleImage);
	doodle::Image image;
};
