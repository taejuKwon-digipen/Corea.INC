#include "Texture.h"
#include "MatrixOperator.h"

coconut::Texture::Texture(const char* filePath)
	: image(Image{filePath}) {}

coconut::Texture::Texture(Image&& Image)
	: image(std::move(Image)) {}

void coconut::Texture::Draw(math::TransformMatrix displayMatrix)
{
	image.init(static_cast<int>(displayMatrix[0][0]), static_cast<int>(displayMatrix[0][1]), static_cast<int>(displayMatrix[0][2]), static_cast<int>(displayMatrix[1][2]));
	image.drawImage();
}

void coconut::Texture::Draw(math::TransformMatrix displayMatrix, glm::ivec2 texelPos, glm::ivec2 frameSize)
{
	image.init(frameSize.x, frameSize.y, texelPos.x, texelPos.y);
	image.drawImage();
}

glm::vec2 coconut::Texture::GetSize()
{
	return image.GetSize();
}

coconut::Texture::Color coconut::Texture::GetPixel(glm::ivec2 pos)
{
	Color color;
	glReadPixels(pos.x, pos.y, 1, 1, GL_RGBA, GL_FLOAT, &color);
	return color;
}