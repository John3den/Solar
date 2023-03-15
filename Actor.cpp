#include "Actor.h"

std::string names[] =
{
	"earth" ,"moon","venus","mars", "mercury", "jupiter",  "saturn", "uranus", "neptune", "sun"
};

Actor::Actor(int index, Shader& shaderProgram): 
	vao(VAO()),
	vbo(VBO(BodyVertices[index], sizeof(BodyVertices[index]))), 
	ebo(EBO(BodyIndices[index], sizeof(BodyIndices[index]))),
	texture(Texture(("Textures/" + names[index] + ".png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)),
	normalMap(Texture(("NormalMaps/" + names[index] + ".png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE))
{
	vao.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 17 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 17 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 17 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, 17 * sizeof(float), (void*)(8 * sizeof(float)));
	vao.LinkAttrib(vbo, 4, 3, GL_FLOAT, 17 * sizeof(float), (void*)(11 * sizeof(float)));
	vao.LinkAttrib(vbo, 5, 3, GL_FLOAT, 17 * sizeof(float), (void*)(14 * sizeof(float)));
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	Texture texture = Texture(("Textures/" + names[index] + ".png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.TexUnit(shaderProgram, "tex0", 0);
	if (index < 9)
	{
		normalMap.TexUnit(shaderProgram, "normal0", 1);
	}
}

VAO Actor::GetVAO()
{
	return vao;
}

VBO Actor::GetVBO()
{
	return vbo;
}
EBO Actor::GetEBO()
{
	return ebo;
}
Texture Actor::GetTexture()
{
	return texture;
}
Texture Actor::GetNormalMap()
{
	return normalMap;
}