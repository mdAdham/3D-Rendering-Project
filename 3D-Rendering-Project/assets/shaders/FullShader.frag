#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Color;
in vec3 Normal;
in vec2 TexCoord;

#define NO_OF_POINT_LIGHTS 32
#define NO_OF_SPOT_LIGHTS 32

uniform vec3 viewPos;

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
uniform bool HasSpotLight;
uniform int spotlightsize;




vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);

	//return vec3(0.0f);
	if (HasMaterial)
	{
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

		vec3 ambient = material.vdiffuse == 0.0f ? light.ambient * vec3(texture(material.diffuse, TexCoord)) : light.ambient * material.vdiffuse;

		vec3 diffuse = material.vdiffuse == 0.0f ? light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)) : light.diffuse * diff * material.vdiffuse;

		vec3 specular = material.vspecular == 0.0f ? light.specular * spec * vec3(texture(material.specular, TexCoord)) : light.specular * spec * material.vspecular;

		return (ambient + diffuse + specular);
	}
	else
	{
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.2);

		vec3 ambient = light.ambient * Color;

		vec3 diffuse = light.diffuse * diff * Color * 0.4;

		vec3 specular = light.specular * spec * Color * 0.3;

		return (ambient + diffuse + specular);
	}
}





vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);


	float distance = length(light.position - FragPos);// * .02;
	//float distance = 1.0;
	float attenuation = min(1.0 / ((light.constant + light.linear *
								distance + light.quadratic * (distance * distance))),
								1.0
								);


	if (HasMaterial)
	{
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

		vec3 ambient = material.vdiffuse == 0.f ? light.ambient * vec3(texture(material.diffuse, TexCoord)) : light.ambient * material.vdiffuse;

		vec3 diffuse = material.vdiffuse == 0.f ? light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)) : light.diffuse * diff * material.vdiffuse;

		vec3 specular = material.vspecular == 0.f ? light.specular * spec * vec3(texture(material.specular, TexCoord)) : light.specular * spec * material.vspecular;

		//return vec3(distance * 0.1);
		
		//return (ambient + diffuse + specular);

		//if (attenuation >= 0.f)
		//	return vec3(attenuation, attenuation, attenuation);

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

vec3 CalculateSpotLight(SpotLight light, vec3 lightDir)
{
	float theta = dot(lightDir, normalize(-light.direction));

	if (theta > light.cutOff)
	{
		float epsilon = light.cutOff - light.outerCutOff;
		float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
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
		result = CalculateDirectionalLight(directionallight, norm, viewDir);

	
	if (HasPointLight)
	{
		for (int i = 0; i < pointlightsize; i++)
			result += CalculatePointLight(pointlights[i], norm, FragPos, viewDir);
	}

	if (HasSpotLight)
	{
		for (int i = 0; i < spotlightsize; i++)
		{
			vec3 lightDir = normalize(spotlights[i].position - FragPos);
			result += CalculateSpotLight(spotlights[i], lightDir);
		}
	}
	
	FragColor = vec4(result, 1.0);
}