#version 430

in vec4 outFragPosition;
in vec3 outFragNormal;
in vec2 outVertexTexCoord;

layout (location=0) out vec4 outFragmentColor;

layout (binding=0) uniform sampler2D textureSampler;
layout (binding=1) uniform sampler2D textureSpecularSampler;

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
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

out vec4 outVertexColor;

void main()
{
   	//vec3 ambient = material.ambient;
   	vec3 ambient = light.ambient * material.ambient;

	vec3 tNormal = outFragNormal;
	vec4 mvPosition = outFragPosition;
	//vec3 positionToLight = normalize(vec3(lightPosition - vec3(mvPosition)));
	vec3 positionToLight = normalize(vec3(light.position - vec3(mvPosition)));

	float diffuseIntensity = max(dot(positionToLight, tNormal), 0.0);
	//vec3 diffuse = lightColor * diffuseIntensity;
	vec3 diffuse = light.diffuse * diffuseIntensity;

	vec3 specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-mvPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, tNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		//specularIntensity = pow(specularIntensity, 16.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		//specular = lightColor * material.specular * specularIntensity;
		specular = light.specular * material.specular * specularIntensity;
	}

	vec4 textureColor = texture(textureSampler, outVertexTexCoord);
	vec4 specularColor = texture(textureSpecularSampler, outVertexTexCoord);

	outVertexColor = (textureColor * vec4(ambient + diffuse, 1.0)) + 
		(specularColor * vec4(specular, 1.0)); 
	//outVertexColor = (textureColor * vec4(ambient + diffuse, 1.0)) + vec4(specular, 1.0); 
	//outVertexColor = fragTexColor;
}