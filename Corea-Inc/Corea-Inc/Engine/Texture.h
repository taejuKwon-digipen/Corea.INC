#pragma once
#include "Image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace coconut
{
	namespace math
	{
		class TransformMatrix;
	}
	class Texture
	{
		struct Color
		{
			GLfloat r;
			GLfloat g;
			GLfloat b;
			GLfloat alpha;
		};
		friend class TextureManager;
		friend class SpriteFont;
	public:
		Texture() {}
		void Draw(math::TransformMatrix displayMatrix);
		void Draw(math::TransformMatrix displayMatrix, glm::ivec2 texelPos, glm::ivec2 frameSize);
		glm::vec2 GetSize();
		Color GetPixel(glm::ivec2 pos);
	private:
		Texture(const char* filePath);
		Texture(Image&& Image);
		Image image;
	};
}