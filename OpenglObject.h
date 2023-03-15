#pragma once

#include<glad/glad.h>

class OpenglObject
{
public:
	virtual void Delete() = 0;
	virtual GLuint GetID();
protected:
	GLuint ID;
};