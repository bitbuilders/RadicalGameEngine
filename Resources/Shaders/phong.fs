#version 410

in vec4 outFragPosition;
in vec3 outFragNormal;

layout (location=0) out vec4 outFragmentColor;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

struct Light
{
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec3 outVertexColor;

void main()
{
   	vec3 ambient = material.ambient;

	vec3 tNormal = outFragNormal;
	vec4 mvPosition = outFragPosition;
	vec3 positionToLight = normalize(vec3(vec3(light.position) - vec3(mvPosition)));

	float diffuseIntensity = max(dot(positionToLight, tNormal), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	vec3 specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-mvPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, tNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = light.specular * material.specular * specularIntensity;
	}

	outVertexColor = ambient + diffuse + specular; 
}