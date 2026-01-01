#include "pch.hpp"
#include "Cube.hpp"
#include <math.h>


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

static unsigned int indicies[] =
{
	2, 1, 3,
	0, 1, 2,

	6, 5, 7,
	4, 5, 6,

	10, 9, 11,
	8, 9, 10,

	14, 13, 15,
	12, 13, 14,

	18, 17, 19,
	16, 17, 18,

	22, 21, 23,
	20, 21, 22
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
		{ ShaderDataType::Float2, "aTexCoord" }
	};

	vbo->SetLayout(lay);
	vao->AddVertexBuffer(vbo);
	vao->SetIndexBuffer(ebo);


	//m_shader.Init("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	//m_shader.Init("assets/shaders/light.vert", "assets/shaders/light.frag");

	diffuse.Load("assets/textures/global_diffuse.png");
	//normal.Load("assets/textures/normal.png");
	specular.Load("assets/textures/specular.png");
}

void Cube::Update()
{
	m_Model = rotate(m_Model, 0.0002f, vec3(0.1f, 0.0f, 0.0f));
}

void Cube::Render(SDL_Window* window, const mat4& view, const mat4& proj, Camera& cam, Shader* m_shader)
{
	

	m_shader->use();

	m_shader->setmat4("uModel", m_Model);

	m_shader->setmat4("uView", view);
	m_shader->setmat4("uProjection", proj);
	m_shader->setvec3("lightColor", vec3(0.82f, 0.82f, 0.82f));
	m_shader->setvec3("lightPos", vec3(0.5f, 1.0f, -1.0f));
	m_shader->setvec3("viewPos", cam.getPos());

	diffuse.Bind(0);
	m_shader->setint("material.diffuse", 0);
	specular.Bind(1);
	m_shader->setint("material.specular", 1);

	m_shader->setfloat("material.shininess", 32.0f);

	vec3 lightColor;
	lightColor.x = 1.0f;
	lightColor.y = 1.0f;
	lightColor.z = 1.0f;

	vec3 diffuseColor = lightColor * vec3(1.0f);
	vec3 ambientColor = diffuseColor * vec3(0.3f);

	m_shader->setvec3("light.ambient", ambientColor);
	m_shader->setvec3("light.diffuse", diffuseColor);
	m_shader->setvec3("light.specular", vec3(1.0f, 1.0f, 1.0f));

	vao->Bind();
	uint32_t count = ebo->GetCount() ? ebo->GetCount() : vao->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void GlobalCube::Init(const vec3& positon)
{
	m_Model = mat4(1.0f);
	m_Model = translate(m_Model, positon);
	//m_Model = rotate(m_Model, 45.f, vec3(1.f, 1.f, 1.f));

	vao = VertexArray::Create();
	vbo = VertexBuffer::Create(vert, sizeof(vert));
	ebo = IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(unsigned int));

	BufferLayout lay = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float3, "aColor" },
		{ ShaderDataType::Float3, "aNormal" },
		{ ShaderDataType::Float2, "aTexCoord" }
	};
	vbo->SetLayout(lay);
	vao->AddVertexBuffer(vbo);
	vao->SetIndexBuffer(ebo);

	material.shininess = 32.f;

#if 0
	material.vdiffuse = 0.9f;
	material.vspecular = 0.1f;
#else
	material.vdiffuse = 0.0f;
	material.vspecular = 0.0f;
#endif


	material.diffuse.Load("assets/textures/global_diffuse.png");
	material.specular.Load("assets/textures/specular.png");

	/*
	material.diffuse.Load("assets/texture/global_diffuse.png");
	material.specular.Load("assets/texture/global_diffuse.png");
	*/

}

void GlobalCube::Update(float dt)
{
	m_Model = rotate(m_Model, .45f * dt, vec3(0.f, 4.f, 0.f));
}

static void PrintUniformPos(const std::vector<string>& vecs, GlobalShader* shader)
{
	for (auto& st : vecs)
	{
		GLint vertexUVID = glGetUniformLocation(shader->getID(), st.c_str());
		cout << st << " : " << vertexUVID << endl;
	}
}

void GlobalCube::Render(SDL_Window* window, const mat4& view, const mat4& proj, glm::vec3& camPos, GlobalShader* shader)
{
	shader->use();

	shader->setmat4("uModel", m_Model);

	shader->setmat4("uView", view);
	shader->setmat4("uProjection", proj);
	shader->setvec3("viewPos", camPos);

	shader->use();
	shader->SetMaterial(material);

	//shader->setint("testdiffuse", 0);
	//material.diffuse.Bind(0);

	//material.diffuse.Bind(0);
	//shader->setint("material.diffuse", 0);
	//material.specular.Bind(1);
	//shader->setint("material.specular", 1);
#if 0


	cout << endl << endl;

	std::vector<string> vecs;

	vecs.push_back("viewPos");
	vecs.push_back("material.vdiffuse");
	vecs.push_back("material.vspecular");
	vecs.push_back("material.diffuse");
	vecs.push_back("material.specular");
	vecs.push_back("material.shininess");
	vecs.push_back("HasMaterial");
	vecs.push_back("directionallight.direction");
	vecs.push_back("directionallight.ambient");
	vecs.push_back("directionallight.diffuse");
	vecs.push_back("directionallight.specular");
	vecs.push_back("HasDirectionalLight");
	vecs.push_back("pointlightsize");
	vecs.push_back("spotlightsize");
	vecs.push_back("testdiffuse");

	PrintUniformPos(vecs, shader);
	
	//cout << glGetError() << endl;
	//exit(0);
#endif //  

	vao->Bind();
	uint32_t count = ebo->GetCount() ? ebo->GetCount() : vao->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
