#version 330

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct Light{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntesity;
};

struct DirectionalLight {
	Light base;
	vec3 direction;
};

struct PointLight{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct Material{
	float specularIntesity;
	float shininess;
};

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;

uniform sampler2D texSampler;
uniform Material material;

uniform vec3 eyePosition;



vec4 CalculateLightByDirection(Light light, vec3 direction){
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;

	float diffuseFactor = max(
		dot(normalize(Normal), normalize(direction)),
		0.0f
	);

	vec4 diffuseColour = vec4(light.colour * light.diffuseIntesity * diffuseFactor, 1.0f);

	vec4 specularColor = vec4(0, 0, 0, 0);

	if(diffuseFactor > 0.0f)
	{
		vec3 FragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));

		float specularFactor = dot(FragToEye, reflectedVertex);

		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.colour * material.specularIntesity * specularFactor, 1.0f);
		}
	}

	return (ambientColour + diffuseColour + specularColor);
}

vec4 CalculateDirectionalLight(){
	return CalculateLightByDirection(
		directionalLight.base, directionalLight.direction
	);
}

vec4 CalculatePointLight(PointLight pLight){
	vec3 direction = FragPos - pLight.position; // direction to fragment
	float distance = length(direction);
	direction = normalize(direction);

	vec4 colour = CalculateLightByDirection(pLight.base, direction); // treat every light to fragment as directional

	float attenuation = pLight.exponent * distance * distance + 
		pLight.linear * distance +
		pLight.constant;

	return (colour / attenuation);
}

vec4 CalculatePointLights(){
	vec4 totalColour = vec4(0, 0, 0, 0);

    totalColour += CalculatePointLight(pointLight);

	return totalColour;
}

void main()
{
    vec4 finalColour = CalculateDirectionalLight();
	finalColour += CalculatePointLights();

    vec4 tempColor = texture(
        texSampler, texCoord
    ) * finalColour;

    if(tempColor.a < 0.2)
        discard;
    
    color = tempColor;
}