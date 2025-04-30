#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Color;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

struct Light
{
	//vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

void main()
{
	float ambientStrength = 0.3;
	float specularStrength = 0.5;
	int specularShininess = 32; //32 Default

	
	//Diffuse
	vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(lightPos - FragPos);
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(norm, lightDir), 0.0);;
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

	//Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	//Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	//Result
	vec3 result = (ambient + diffuse + specular);

	FragColor = vec4(result, 1.0);
	//FragColor = texture(material.diffuse, TexCoord);
}