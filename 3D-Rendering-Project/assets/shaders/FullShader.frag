#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Color;
in vec3 Normal;
in vec2 TexCoord;

#define NO_OF_POINT_LIGHTS 32
#define NO_OF_SPOT_LIGHTS 32


struct Material
{
	float vdiffuse;
	float vspecular;

	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;
uniform bool HasMaterial;

struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirectionalLight directionallight;
uniform bool HasDirectionalLight;

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform PointLight pointlights[NO_OF_POINT_LIGHTS];
uniform bool HasPointLight;
uniform int pointlightsize;

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float cutOff; //angle
	float outerCutOff;  //angle

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
uniform SpotLight spotlights[NO_OF_SPOT_LIGHTS];
uniform bool HadSpotLight;
uniform int spotlightsize;




vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);

	if (HasMaterial)
	{
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material,shininess);

		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

		return (ambient + diffuse + specular);
	}
	else
	{
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material,shininess);

		vec3 ambient = light.ambient * Color;

		vec3 diffuse = light.diffuse * diff * Color * 0.4;

		vec3 specular = light.specular * spec * Color * 0.3;

		return (ambient + diffuse + specular);
	}
}





vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);


	float distance = length(pointlight[i].position - FragPos);
	float attenuation = 1.0 / (pointlight[i].constant + pointlight[i].linear *
								distance + light.quadratic * (distance * distance));

	if (HasMaterial)
	{
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		return (ambient + diffuse + specular);
	}

	else 
	{
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.2);

		vec3 ambient = light.ambient * Color;

		vec3 diffuse = light.diffuse * diff * Color * 0.2;

		vec3 specular = light.specular * spec * Color * 0.2;

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		return (ambient + diffuse + specular);
	}
}

vec3 calculatespotlight(SpotLight light, vec3 lightDir)
{
	float theta = dot(lightDir, normalize(-light.direction));

	if (theta > light.cutOff)
	{
		float epsilon = spotlight[index].cutOff - spotlight[index].outerCutOff;
		float intensity = clamp((theta - spotlight[index].outerCutOff) / epsilon, 0.0, 1.0);
	}
	else
		return vec3(0);
}



void main()
{	
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result;
	if (HasDirectionalLight)
		result = CalculateDirectionalLight(directionalLight, norm, viewDir);

	if (HasPointLight)
	{
		for (int i = 0; i < pointlightsize; i++)
			result += CalculatePointLight(pointlights[i], norm, FragPos, viewDir);
	}

	if (HasSpotLight)
	{
		for (int i = 0; i < spotlightsize; i++)
		{
			vec3 lightDir = normalize(spotlight.position - fragPos);
			result += CalculateSpotLight(spotlight[i], lightDir);
		}
	}

	FragColor = vec4(result, 1.0);
}