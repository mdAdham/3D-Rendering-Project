#include "pch.hpp"
#include "Light.hpp"

static unsigned int indicies[] =
{
	0, 1, 2,
	2, 1, 3,

	4, 5, 6,
	6, 5, 7,

	8, 9, 10,
	8, 10, 11,

	12, 13, 14,
	12, 14, 15,

	16, 17, 18,
	16, 18, 19,

	20, 21, 22,
	20, 22, 23
};

static Vertex vert[] = {
	//Front
	{ {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f } },
	{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f } },
	{ {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f } },
	{ { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f } },

	//Right
	{ { 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f } },
	{ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f } },
	{ { 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f } },
	{ { 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f } },

	//Left
	{ { -0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f } }, //top back
	{ { -0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f } }, //bottom back
	{ { -0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f } }, //bottom front
	{ { -0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f } }, //top front

	//Back
	{ { -0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f } }, //left down
	{ { -0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f } }, //left up
	{ {  0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f } }, //right up
	{ {  0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f } }, //right down

	//Top
	{ { -0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f } },
	{ { -0.5f, 0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f } },
	{ {  0.5f, 0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f } },
	{ {  0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f } },

	//Bottom
	{ { -0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f } },
	{ {  0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f } },
	{ {  0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f } },
	{ { -0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f } }
};

Light::Light(const vec3& positon, const vec3& color)
{
	Init(positon, color);
}

Light::~Light()
{
}

void Light::Init(const vec3& positon, const vec3& color)
{
	m_Model = mat4(1.0f);
	m_Model = translate(m_Model, positon);
	m_Color = color;

	vao = VertexArray::Create();
	vbo = VertexBuffer::Create(vert, sizeof(vert));
	ebo = IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(unsigned int));

	BufferLayout lay = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float3, "aColor" },
		{ ShaderDataType::Float3, "aNormal" },
		{ ShaderDataType::Float2, "aTexCoord" },
	};

	vbo->SetLayout(lay);
	vao->AddVertexBuffer(vbo);
	vao->SetIndexBuffer(ebo);


	//m_shader.Init("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	m_lightshader.Init("assets/shaders/light.vert", "assets/shaders/light.frag");
}

void Light::Update()
{
	
}

void Light::Render(SDL_Window* window, const mat4& view, const mat4& proj)
{
	m_lightshader.use();
	m_lightshader.setmat4("uModel", m_Model);
	m_lightshader.setmat4("uView", view);
	m_lightshader.setmat4("uProjection", proj);

	m_lightshader.setvec3("lightColor", m_Color);

	vao->Bind();
	uint32_t count = ebo->GetCount() ? ebo->GetCount() : vao->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
