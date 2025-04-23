#include "pch.hpp"
#include "Cube.hpp"

static float verticies[] =
{
	// Front - Z Constant
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,

	 // Right
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f
};

static unsigned int indicies[] =
{
	0, 1, 2,
	2, 1, 3,
	4, 5, 6,
	6, 5, 7
};

Cube::Cube(const vec3& positon, float length, float bredth)
{
	m_Model = mat4(1.0f);
	m_Model = translate(m_Model, positon);
}

Cube::~Cube()
{
}

void Cube::Init(const vec3& positon, float length, float bredth)
{
	m_Model = mat4(1.0f);

	vao = VertexArray::Create();
	vbo = VertexBuffer::Create(verticies, sizeof(verticies));
	ebo = IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(unsigned int));

	BufferLayout lay = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float3, "aColor" }
	};

	vbo->SetLayout(lay);
	vao->AddVertexBuffer(vbo);
	vao->SetIndexBuffer(ebo);

	m_Model = translate(m_Model, positon);

	shader.Init("assets/shaders/basic.vert", "assets/shaders/basic.frag");
}

void Cube::Update()
{
}

void Cube::Render(SDL_Window* window, const mat4& view, const mat4& proj)
{
	shader.use();
	shader.setmat4("uModel", m_Model);
	shader.setmat4("uView", view);
	shader.setmat4("uProjection", proj);

	vao->Bind();
	uint32_t count = ebo->GetCount() ? ebo->GetCount() : vao->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
