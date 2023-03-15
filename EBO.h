#pragma once
#include <glad/glad.h>

#include "OpenglBuffer.h"

class EBO : public OpenglBuffer
{
public:
	EBO(GLuint* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};
