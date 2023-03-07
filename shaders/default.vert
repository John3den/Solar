#version 420 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normals (not necessarily normalized)
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aTangent;
layout (location = 5) in vec3 aBitangent;

// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;
out vec3 lightPosition;
out vec3 camPosition;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
// Imports the model matrix from the main function
uniform mat4 model;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;


void main()
{
	mat3 TBN = mat3(aTangent, aBitangent, aNormal);
	TBN = transpose(TBN);

	camPosition = TBN * camPos;
	lightPosition = TBN * lightPos;
	// calculates current position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	crntPos= TBN * crntPos;
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = vec3(model*vec4(aNormal,0.0f));

}