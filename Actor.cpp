#include "Actor.h"

Actor::Actor(float radius): 
	Geometry(radius),
	vao(VAO()),
	vbo(VBO(vertices, sizeof(vertices))),
	ebo(EBO(indices, sizeof(indices)))
{
	vao.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(8 * sizeof(float)));
	vao.LinkAttrib(vbo, 4, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(11 * sizeof(float)));
	vao.LinkAttrib(vbo, 5, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(14 * sizeof(float)));
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}
