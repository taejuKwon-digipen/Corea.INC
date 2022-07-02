//TaejuKwon

#include "../Header/TexelImage.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <array>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace coconut;

TexelImage::GLModel TexelImage::mdl;
TexelImage::Vertex vertex;
std::vector<TexelImage::Vertex> TexelImage::vertices;
TexelImage texelImage;


TexelImage::TexelImage()
{
	width = 800;
	height = 500;
	vaoid = 0;
	xpos = 0;
	ypos = 0;
	tex = false;
}

TexelImage::TexelImage(const char* _filepath) : filepath(_filepath) {
	width = 800, height = 500;
	vaoid = 0;
	xpos = 0;
	ypos = 0;
};

GLuint setup_texobj(const char* _pathname) {
	//unsigned int VBO, EBO;
	int width{ 256 }, height{ 256 }, bytes_per_texel{ 4 };
	int nrChannels;
	GLuint texobj_hdl;
	glGenTextures(1, &texobj_hdl);
	glBindTexture(GL_TEXTURE_2D, texobj_hdl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(_pathname, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return texobj_hdl;
}

void TexelImage::init(const char* _filepath, int x, int y, int texel_X, int texel_Y, int texel_W, int texel_H) {
	//Left Bottom
	glClearColor(1.f, 1.f, 1.f, 1.f);
	xpos = x;
	ypos = y;
	width = 800; //��ü width (g_nPandaWidth)
	height = 500 ; //��ü height
	texel_x = texel_X; texel_h = texel_H; texel_y = texel_Y; texel_w = texel_W;
	glViewport(x, y, width, height);
	mdl.setup_vao();
	mdl.setup_shdrpgm();
	mdl.shdr_pgm.Use();

	texobj_hdl0 = setup_texobj(_filepath);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TexelImage::drawTexelImage() {
	glClear(GL_COLOR_BUFFER_BIT);
	mdl.draw(texobj_hdl0);
}

void TexelImage::GLModel::setup_vao()
{
	unsigned int VBO, EBO;

	std::array<glm::vec2, 4> pos_vtx{
		glm::vec2(texelImage.texel_x + texelImage.texel_w, texelImage.texel_y),						// RIGHT | TOP
		glm::vec2(texelImage.texel_x + texelImage.texel_w, texelImage.texel_y + texelImage.texel_h),// RIGHT | BOTTOM
		glm::vec2(texelImage.texel_x,					   texelImage.texel_y + texelImage.texel_h),// LEFT  | BOTTOM
		glm::vec2(texelImage.texel_x ,					   texelImage.texel_y)						// LEFT  | TOP
	};

	std::array<glm::vec3, 4> clr_vtx{
	glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f),
	glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f)
	};
	std::array<glm::vec2, 4> tex_vtx{
	glm::vec2(texelImage.texel_x / texelImage.width, texelImage.texel_y / texelImage.height),
	glm::vec2(texelImage.texel_x / texelImage.width, (texelImage.texel_y + texelImage.texel_h) / texelImage.height),
	glm::vec2((texelImage.texel_x + texelImage.texel_w) / texelImage.width, (texelImage.texel_y + texelImage.texel_h) / texelImage.height),
	glm::vec2((texelImage.texel_x + texelImage.texel_w) / texelImage.width, texelImage.texel_y / texelImage.height)
	};

	vertices.push_back({ pos_vtx[0],clr_vtx[0],tex_vtx[0] });
	vertices.push_back({ pos_vtx[1],clr_vtx[1],tex_vtx[1] });
	vertices.push_back({ pos_vtx[2],clr_vtx[2],tex_vtx[2] });
	vertices.push_back({ pos_vtx[3],clr_vtx[3],tex_vtx[3] });

	primitive_type = GL_TRIANGLE_STRIP;
	std::array<GLushort, 4> idx_vtx{ 1,2,0,3 };
	idx_elem_cnt = (GLuint)idx_vtx.size();

	glGenVertexArrays(1, &vaoid);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(vaoid);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx_vtx.size() * sizeof(unsigned int), &idx_vtx[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void TexelImage::GLModel::setup_shdrpgm()
{
	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/image.vert"));
	shdr_files.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/image.frag"));
	shdr_pgm.CompileLinkValidate(shdr_files);

	if (GL_FALSE == shdr_pgm.IsLinked()) {
		std::cout << "Unable to compile/link/validate shader programs" << "\n";
		std::cout << shdr_pgm.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void TexelImage::GLModel::draw(GLuint texobj_hdl)
{
	shdr_pgm.Use();
	glBindVertexArray(TexelImage::mdl.vaoid);
	glBindTextureUnit(6, texobj_hdl);
	GLuint tex_loc = glGetUniformLocation(TexelImage::mdl.shdr_pgm.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 6);
	glDrawElements(primitive_type, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	shdr_pgm.UnUse();
}

glm::vec2 TexelImage::getPos()
{
	glm::vec2 pos = glm::vec2{ xpos ,ypos };
	return pos;
}

glm::vec2 TexelImage::GetSize()
{
	glm::vec2 size = glm::vec2{ width ,height };
	return size;
}


