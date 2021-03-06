#version 430

in vec4 outFragPosition;
in vec3 outFragNormal;
in vec2 outVertexTexCoord;

layout (location=0) out vec4 outFragmentColor;

layout (binding=0) uniform sampler2D textureSampler;

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
//uniform Light light;
uniform Light lights[100];

uniform int numOfLights = 0;

//uniform vec3 lightPosition;
//uniform vec3 lightColor;


out vec4 outVertexColor;

void phong(int lightIndex, vec3 position, vec3 normal, out vec3 diff, out vec3 spec) 
{
   	//vec3 ambient = lights[lightIndex].ambient * material.ambient;
	
	vec3 tNormal = normal;
	vec4 mvPosition = vec4(position, 1.0);

	vec3 directionToLight;
	if (lights[lightIndex].position.w == 0)
	{
		directionToLight = normalize(vec3(lights[lightIndex].position));
	}
	else
	{
		directionToLight = normalize(vec3(lights[lightIndex].position) - vec3(mvPosition));
	}

	float diffuseIntensity = max(dot(directionToLight, tNormal), 0.0);
	vec3 diffuse = lights[lightIndex].diffuse * material.diffuse * diffuseIntensity;

	// diffuse lighting calculations that were in main
	diff = diffuse;

	vec3 specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-mvPosition.xyz);
		vec3 reflectLightVector = reflect(-directionToLight, tNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		//specularIntensity = pow(specularIntensity, 16.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		//specular = lightColor * specularMaterial * specularIntensity;
		specular = lights[lightIndex].specular * material.specular * specularIntensity;
		spec = lights[lightIndex].specular * material.specular * specularIntensity;
	}

	// specular calculations that were in main
}
/*
void phong(vec3 position, vec3 normal, out vec3 ambientDiffuse, out vec3 spec) 
{
   	vec3 ambient = light.ambient * material.ambient;

	vec3 tNormal = normal;
	vec4 mvPosition = vec4(position, 1.0);

	vec3 directionToLight;
	if (light.position.w == 0)
	{
		directionToLight = normalize(vec3(light.position));
	}
	else
	{
		directionToLight = normalize(vec3(light.position) - vec3(mvPosition));
	}

	float diffuseIntensity = max(dot(directionToLight, tNormal), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	// ambient/diffuse lighting calculations that were in main
	ambientDiffuse = ambient + diffuse;

	vec3 specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-mvPosition.xyz);
		vec3 reflectLightVector = reflect(-directionToLight, tNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		//specularIntensity = pow(specularIntensity, 16.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		//specular = lightColor * specularMaterial * specularIntensity;
		specular = light.specular * material.specular * specularIntensity;
		spec = light.specular * material.specular * specularIntensity;
	}

	// specular calculations that were in main
}
*/

void main()
{
/*
   	//vec3 ambient = ambientMaterial;
   	vec3 ambient = light.ambient * material.ambient;

	vec3 tNormal = outFragNormal;
	vec4 mvPosition = outFragPosition;
	//vec3 positionToLight = normalize(vec3(lightPosition - vec3(mvPosition)));
	//vec3 positionToLight = normalize(vec3(light.position) - vec3(mvPosition));
	
	vec3 directionToLight;
	if (light.position.w == 0)
	{
		directionToLight = normalize(vec3(light.position));
	}
	else
	{
		directionToLight = normalize(vec3(light.position) - vec3(mvPosition));
	}

	float diffuseIntensity = max(dot(directionToLight, tNormal), 0.0);
	//vec3 diffuse = lightColor * diffuseMaterial * diffuseIntensity;
	//vec3 diffuse = lightColor * diffuseIntensity;
	vec3 diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	vec3 specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-mvPosition.xyz);
		vec3 reflectLightVector = reflect(-directionToLight, tNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		//specularIntensity = pow(specularIntensity, 16.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		//specular = lightColor * specularMaterial * specularIntensity;
		specular = light.specular * material.specular * specularIntensity;
	}

	vec4 texel0 = texture(textureSampler, outVertexTexCoord);

	vec4 fragTexColor = texel0;

	o
	utVertexColor = vec4(ambient + diffuse, 1.0) + vec4(specular, 1.0); 
	//outVertexColor = fragTexColor * vec4(ambient + diffuse, 1.0) + vec4(specular, 1.0); 
	//outVertexColor = fragTexColor;
	*/

	vec3 color = material.ambient;
	for (int i = 0; i < numOfLights; i++)
	{
		vec3 diffuse;
		vec3 specular;
		phong(i, vec3(outFragPosition), outFragNormal, diffuse, specular);
		color += (diffuse + specular);
	}
	
    outFragmentColor = vec4(color, 1.0);

	/*
	vec3 tNormal = outFragNormal;
	vec4 mvPosition = outFragPosition;

	vec3 ambientDiffuse;
	vec3 specular;
	phong(vec3(mvPosition), tNormal, ambientDiffuse, specular);
    outFragmentColor = vec4(ambientDiffuse + specular, 1.0);
	*/
}
