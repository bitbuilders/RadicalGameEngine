#version 430

in vec3 outFragPosition;
in vec3 outFragNormal;
in vec2 outTexCoord;
in vec4 shadowCoordFragment;

layout (location=0) out vec4 outFragmentColor;
layout (binding = 0) uniform sampler2D diffuseMap;
layout (binding = 1) uniform sampler2DShadow shadowMap;

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

out vec4 outFragColor;

float calculateShadow()
{
	float bias = 0.005;
	// shadow = 1.0 (not in shadow)
	// shadow = 0.0 (in shadow)
	float shadow = texture(shadowMap, vec3(shadowCoordFragment.xy, 
		(shadowCoordFragment.z)/shadowCoordFragment.w) - bias);

	return shadow;
}

void phong(vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular)
{
	vec3 tNormal = normal;
	vec3 mvPosition = position;
	vec3 positionToLight = normalize(vec3(vec3(light.position) - vec3(mvPosition)));

	float diffuseIntensity = max(dot(positionToLight, tNormal), 0.0);
	diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	specular = vec3(0.0);
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
   	vec3 ambient = material.ambient;

	vec3 diffuse;
	vec3 specular;
	phong(outFragPosition, outFragNormal, diffuse, specular);

	vec4 textureColor = texture(diffuseMap, outTexCoord);
	float shadow = calculateShadow();
    outFragColor = textureColor * vec4(ambient + ((diffuse + specular) * shadow), 1.0);

	//outFragColor = ambient + diffuse + specular; 
}