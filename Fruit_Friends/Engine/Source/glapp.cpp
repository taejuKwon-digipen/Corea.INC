#include "../Header/glapp.h"
#include "../Header/glhelper.h"
#include "../Header/glslshader.h"

GLApp::GLModel GLApp::mdl;
std::array<glm::vec2, 4> pos_vtx;
std::array<glm::vec3, 4> clr_vtx;

void GLApp::init() {
	glClearColor(1.f, 1.f, 1.f, 1.f);
	GLint w{ GLHelper::width }, h{ GLHelper::height };
	glViewport(0, 0, w, h);
}

void GLApp::update([[maybe_unused]]double delta_time)
{
	//Timer += delta_time;
}

void GLApp::GLModel::setup_posvtx(glm::vec2 one, glm::vec2 two, glm::vec2 three, glm::vec2 four)
{

	unsigned int VBO, EBO;
	// Define vertex position and color attributes
	std::array<glm::vec2, 4> pos_vtx {
	one, two, three,  four
	};

	std::array<glm::vec3, 4> clr_vtx{
	glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f),
	glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f)
	};
	/*std::array<glm::vec2, 4> tex_vtx{
	glm::vec2(0.f, 0.f), glm::vec2(0.f, 1.f),
	glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f)
	};*/

	vertices.push_back({ pos_vtx[0],clr_vtx[0] });
	vertices.push_back({ pos_vtx[1],clr_vtx[1] });
	vertices.push_back({ pos_vtx[2],clr_vtx[2] });
	vertices.push_back({ pos_vtx[3],clr_vtx[3] });

	primitive_type = GL_TRIANGLE_STRIP;
	std::array<GLushort, 4> idx_vtx{ 0, 1,3,2 };
	idx_elem_cnt = idx_vtx.size();

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
	//// vertex texture coords
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void GLApp::GLModel::draw()
{
	//GLuint texobj_hdl0 = setup_texobj("../images/duck-rgba-256.tex");
	glBindVertexArray(GLApp::mdl.vaoid);
	//glBindTextureUnit(6, texobj_hdl0);
	//GLuint tex_loc = glGetUniformLocation(GLApp::mdl.shdr_pgm.GetHandle(), "uTex2d");
	//glUniform1i(tex_loc, 6);
	glDrawElements(primitive_type, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	//shdr_pgm.UnUse();
}
