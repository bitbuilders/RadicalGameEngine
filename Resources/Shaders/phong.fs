#version 410

in vec4 outFragPosition;
in vec3 outFragNormal;

layout (location=0) out vec4 outFragmentColor;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;

uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec3 outVertexColor;

void main()
{
   	vec3 ambient = ambientMaterial;

	vec3 tNormal = outFragNormal;
	vec4 mvPosition = outFragPosition;
	vec3 positionToLight = normalize(vec3(lightPosition - vec3(mvPosition)));

	float diffuseIntensity = max(dot(positionToLight, tNormal), 0.0);
	vec3 diffuse = lightColor * diffuseMaterial * diffuseIntensity;

	vec3 specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-mvPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, tNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, 16.0);
		specular = lightColor * specularMaterial * specularIntensity;
	}

	outVertexColor = ambient + diffuse + specular; 
}