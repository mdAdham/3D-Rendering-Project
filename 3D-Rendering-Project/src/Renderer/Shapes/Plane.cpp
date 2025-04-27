#include "pch.hpp"
#include "Plane.hpp"

static float vertices[] =
{
	-0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
};

static unsigned int indicies[] =
{
	0, 2, 1,
	1, 3, 2
};

Plane::Plane(const vec3& positon, float length, float bredth)
{
	m_Model = mat4(1.0f);
	m_Model = translate(m_Model, positon);
}

Plane::~Plane()
{
	
}

void Plane::Init(const vec3& positon, float length, float bredth)
{
	m_Model = mat4(1.0f);

	vao = CreateRef<VertexArray>();
	vbo = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
	ebo = CreateRef<IndexBuffer>(indicies, sizeof(indicies) / sizeof(unsigned int));

	BufferLayout lay = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float3, "aColor" },
		{ ShaderDataType::Float2, "aTexCoord"}
	};

	vbo->SetLayout(lay);
	vao->AddVertexBuffer(vbo);
	vao->SetIndexBuffer(ebo);

	m_Model = translate(m_Model, positon);
	m_Model = rotate(m_Model, radians(90.f), vec3(1.0f, 0.0f, 0.0f));
	m_Model = scale(m_Model, vec3(length, 0.0f, bredth));

	tex.Load("assets/textures/Texture.jpg");
	shader.Init("assets/shaders/Texture.vert", "assets/shaders/Texture.frag");
}

void Plane::Update()
{
}

void Plane::Render(SDL_Window* window, const mat4& view, const mat4& proj)
{
	tex.Bind();
	shader.use();

	shader.setmat4("uModel", m_Model);
	shader.setmat4("uView", view);
	shader.setmat4("uProjection", proj);

	vao->Bind();
	uint32_t count = ebo->GetCount() ? ebo->GetCount() : vao->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	tex.Unbind();
}
