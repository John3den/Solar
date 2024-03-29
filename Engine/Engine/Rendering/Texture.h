#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaderClass.h"
#include "OpenglBuffer.h"

namespace Engine
{
	class Texture : public OpenglBuffer
	{
	public:
		Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

		GLenum GetType();

		void TexUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();

	private:
		const GLenum type;
	};
}