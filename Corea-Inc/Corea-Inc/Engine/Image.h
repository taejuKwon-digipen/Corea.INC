#pragma once
#include <string>
#include <memory>
#include <GL/glew.h>
#include <filesystem>
#include "glslshader.h"

namespace coconut
{
	class Image
	{
	private:
		static int width, height, xPos, yPos;
		static unsigned int texture;
		const char* filepath;
		GLSLShader shdr_pgm;
		GLuint texobj_hdl;
		GLuint vaoid;
		bool tex;
	public:
		Image();
		Image(const char* _filepath);
		Image(const char* _filepath, int w, int h);
		void init(int x, int y, int w, int h);
		void drawImage();

		struct GLModel
		{
			GLenum primitive_type;
			GLSLShader shdr_pgm;
			GLuint vaoid;
			GLuint idx_elem_cnt;
			void setup_vao();
			void setup_shdrpgm();
			void draw(GLuint texobj_hdl);
		};
		struct Vertex {
			glm::vec2 Position;
			glm::vec3 Color;
			glm::vec2 TexCoords;
		};
		struct Texture {
			unsigned int id;
			std::string type;
		};

		static std::vector<Vertex> vertices;
		static GLModel mdl;

		static glm::vec2 GetPos();
		static glm::vec2 GetSize();
		static unsigned int GetTextureInt();
		static void begin_drawing_to_image(int x, int y, bool _tex);
		static Image& end_drawing_to_image();
	};
}