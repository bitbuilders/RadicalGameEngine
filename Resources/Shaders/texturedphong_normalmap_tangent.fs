#version 430

in vec4 outFragPosition;
in vec3 outFragNormal;
in vec2 outVertexTexCoord;

layout (location=0) out vec4 outFragmentColor;

layout (binding=0) uniform sampler2D textureSampler;
layout (binding = 1) uniform sampler2D normalMap;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

//uniform vec3 ambientMaterial;
//uniform vec3 diffuseMaterial;
//uniform vec3 specularMaterial;

struct Light
{
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

//uniform vec3 lightPosition;
//uniform vec3 lightColor;


out vec4 outVertexColor;

void phong(vec3 position, vec3 normal, out vec3 ambientDiffuse, out vec3 specular)
{
   	vec3 ambient = material.ambient;

	vec3 tNormal = normal;
	vec4 mvPosition = vec4(position, 1.0f);
	vec3 positionToLight = normalize(vec3(light.position) - vec3(mvPosition));

	float diffuseIntensity = max(dot(positionToLight, tNormal), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	ambientDiffuse = ambient + diffuse;

	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-mvPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, tNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = light.specular * material.specular * specularIntensity;
	}
}

void main()
{
	vec4 texel0 = texture(textureSampler, outVertexTexCoord);

	vec3 normal = texture(normalMap, outVertexTexCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 ambientDiffuse;
	vec3 specular;
	phong(vec3(outFragPosition), normal, ambientDiffuse, specular); 

	vec4 fragTexColor = texel0 * vec4(ambientDiffuse, 1.0f) + vec4(specular, 1.0f);
 
	outVertexColor = fragTexColor;
}