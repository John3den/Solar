#version 420 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;
in vec3 camPosition;
in vec3 lightPosition;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
uniform sampler2D normal0;
// Gets the color of the light from the main function
uniform vec4 lightColor;


void main()
{
	// ambient lighting
	float ambient = 0.20f;
	vec3 normal = normalize(texture(normal0, texCoord).xyz * 2.0f - 1.0f);
	vec3 lightDirection = normalize(lightPosition - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPosition - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	// outputs final color
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}