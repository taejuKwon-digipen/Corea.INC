#pragma once
#include <string>
#include <memory>
#include <GL/glew.h>
#include "glslshader.h"
#include <filesystem>

namespace coconut {
	class TexelImage {
	private:
		int width, height, nrChannels, xpos, ypos;
		int texel_x, texel_y, texel_w, texel_h;
		const char* filepath;
		GLSLShader shdr_pgm;
		GLuint texobj_hdl0;
		GLuint vaoid;
		bool tex;
	public:
		TexelImage();
		TexelImage(const char* _filepath);
		void init(const char* _filepath, int x, int y,int texel_x, int texel_y, int texel_w, int texel_h);
		void drawTexelImage();

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

		glm::vec2 getPos();
		glm::vec2 GetSize();
	};
}
