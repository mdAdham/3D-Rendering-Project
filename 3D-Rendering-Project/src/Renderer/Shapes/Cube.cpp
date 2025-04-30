#include "pch.hpp"
#include "Cube.hpp"
#include <math.h>

/*
float cubeVertices[] = {
	// positions         // normals          // texCoords
	// Front face
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

	// Back face
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 1.0f,

	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 0.0f,

	// Left face
	-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

	// Right face
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,

	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

	 // Top face
	 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
	  0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

	  0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	  0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

	 // Bottom face
	 -0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
	  0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 0.0f,

	  0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 1.0f
};
*/

static float verticies[] =
{
	// Front - Z Constant
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,

	 // Right
	 0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,

	 // Left
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,

	//Back
	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 1.0f,

	 //Top
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,

	 //Bottom
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f
};
/*
unsigned int cubeIndices[] = {
	0, 1, 2,  2, 3, 0,      // front
	4, 5, 6,  6, 7, 4,      // back
	8, 9,10, 10,11, 8,      // left
   12,13,14, 14,15,12,      // right
   16,17,18, 18,19,16,      // top
   20,21,22, 22,23,20       // bottom
};*/

static unsigned int indicies[] =
{
	0, 1, 2,
	2, 1, 3,

	4, 5, 6,
	6, 5, 7,

	8, 9, 10,
	10, 9, 11,

	12, 13, 14,
	14, 13, 15,

	16, 17, 18,
	18, 17, 19,

	20, 21, 22,
	22, 21, 23
};

static Vertex vert[] = {
	//Front
	{ {-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f } },
	{ { 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f } },
	{ {-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f } },
	{ { 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f } },

	//Right
	{ { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f } },
	{ { 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f } },
	{ { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f } },
	{ { 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f } },

	//Left
	{ { -0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f } }, //top back
	{ { -0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f } }, //bottom back
	{ { -0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f } }, //bottom front
	{ { -0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f } }, //top front

	//Back
	{ {  0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f } }, //left down
	{ { -0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f } }, //left up
	{ {  0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f } }, //right up
	{ { -0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f } }, //right down

	//Top
	{ { -0.5f, 0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f } },
	{ {  0.5f, 0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f } },
	{ { -0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f } },
	{ {  0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f } },

	//Bottom
	{ { -0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f } },
	{ {  0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f } },
	{ { -0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f } },
	{ {  0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f } }
};

Cube::Cube(const vec3& positon, float length, float bredth)
{
	Init(positon, length, bredth);
}

Cube::~Cube()
{
}

void Cube::Init(const vec3& positon, float length, float bredth)
{
	m_Model = mat4(1.0f);
	m_Model = translate(m_Model, positon);
	
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
	m_shader.Init("assets/shaders/light.vert", "assets/shaders/light.frag");

	diffuse.Load("assets/textures/diffuse.png");
	normal.Load("assets/textures/normal.png");
	specular.Load("assets/textures/specular.png");
}

void Cube::Update()
{
	//m_Model = translate(m_Model, vec3(0.1f, 0.0f, 0.0f));
}

void Cube::Render(SDL_Window* window, const mat4& view, const mat4& proj, Camera& cam, Shader* shader)
{
	if (shader)
		m_shader = *shader;

	m_shader.use();
	if (!shader)
		m_shader.setmat4("uModel", m_Model);

	m_shader.setmat4("uView", view);
	m_shader.setmat4("uProjection", proj);
	m_shader.setvec3("lightColor", vec3(0.82f, 0.82f, 0.82f));
	m_shader.setvec3("lightPos", vec3(0.5f, 1.0f, -1.0f));
	m_shader.setvec3("viewPos", cam.getPos());

	diffuse.Bind(0);
	m_shader.setint("material.diffuse", 0);
	specular.Bind(1);
	m_shader.setint("material.specular", 1);
	m_shader.setfloat("material.shininess", 32.0f);

	vec3 lightColor;
	lightColor.x = 1.0f;
	lightColor.y = 1.0f;
	lightColor.z = 1.0f;

	vec3 diffuseColor = lightColor * vec3(1.0f);
	vec3 ambientColor = diffuseColor * vec3(0.3f);

	m_shader.setvec3("light.ambient", ambientColor);
	m_shader.setvec3("light.diffuse", diffuseColor);
	m_shader.setvec3("light.specular", vec3(1.0f, 1.0f, 1.0f));

	vao->Bind();
	uint32_t count = ebo->GetCount() ? ebo->GetCount() : vao->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
