#include "Geometry.h"

Geometry::Geometry(float radius)
{
	for (int j = 0; j < GEOMETRY_RESOLUTION; j++)
		for (int i = 0; i < GEOMETRY_RESOLUTION; i++)
		{
			float x, y, z;
			float phi = 2 * PI * i / ((float)(GEOMETRY_RESOLUTION - 1));
			float theta = j * PI / (GEOMETRY_RESOLUTION - 1);

			x = radius * (sin(theta)) * cos(phi);
			y = radius * cos(theta);
			z = radius * (sin(theta)) * sin(phi);

			glm::vec3 pos(x, y, z);
			glm::vec3 normal = glm::normalize(pos);
			glm::vec2 texCoordinate(phi / (2.0f * PI), (PI - theta) / PI);
			// VERTEX POSITION
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE)] = x;
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 1] = y;
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 2] = z;
			// raw color
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 3] = 0;
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 4] = 0;
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 5] = 0;
			//TEXTURE COORDINATES
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 6] = texCoordinate.x;
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 7] = texCoordinate.y;
			//NORMAL
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 8] = normal.x;
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 9] = normal.y;
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 10] = normal.z;
			//TANGENT
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 11] = -sin(theta) * cos(phi);
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 12] = 0;
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 13] = sin(theta) * cos(phi);
			//BITANGENT
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 14] = cos(theta) * cos(phi);
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 15] = -sin(theta);
			vertices[(GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE) + 16] = cos(theta) * sin(phi);
		}
	for (int j = 0; j < GEOMETRY_RESOLUTION - 1; j++)
	{
		for (int k = 0; k < GEOMETRY_RESOLUTION; k++)
		{
			indices[(j * GEOMETRY_RESOLUTION + k) * 6 + 0] = (j * GEOMETRY_RESOLUTION) + k;
			indices[(j * GEOMETRY_RESOLUTION + k) * 6 + 1] = (j * GEOMETRY_RESOLUTION) + k + 1;
			indices[(j * GEOMETRY_RESOLUTION + k) * 6 + 2] = (j * GEOMETRY_RESOLUTION) + k + GEOMETRY_RESOLUTION;

			indices[(j * GEOMETRY_RESOLUTION + k) * 6 + 3] = (j * GEOMETRY_RESOLUTION) + k + 1;
			indices[(j * GEOMETRY_RESOLUTION + k) * 6 + 4] = (j * GEOMETRY_RESOLUTION) + k + GEOMETRY_RESOLUTION;
			indices[(j * GEOMETRY_RESOLUTION + k) * 6 + 5] = (j * GEOMETRY_RESOLUTION) + k + GEOMETRY_RESOLUTION + 1;
		}
		indices[(j * GEOMETRY_RESOLUTION + GEOMETRY_RESOLUTION - 1) * 6 + 3] = (j * GEOMETRY_RESOLUTION);
		indices[(j * GEOMETRY_RESOLUTION + GEOMETRY_RESOLUTION - 1) * 6 + 4] = (j * GEOMETRY_RESOLUTION) + GEOMETRY_RESOLUTION;
		indices[(j * GEOMETRY_RESOLUTION + GEOMETRY_RESOLUTION - 1) * 6 + 5] = (j * GEOMETRY_RESOLUTION) + GEOMETRY_RESOLUTION - 1;
	}
}