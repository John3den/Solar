#pragma once

#include<glad/glad.h>
namespace Engine
{
	class OpenglObject
	{
	public:
		virtual void Delete() = 0;
		virtual GLuint GetID();
	protected:
		GLuint ID;
	};
}