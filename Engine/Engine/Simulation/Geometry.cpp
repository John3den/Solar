#include "pch.h"
#include "framework.h"
#include "Geometry.h"
namespace Engine
{
	Geometry::Geometry(float radius)
	{
		int offset;
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
				offset = (GEOMETRY_RESOLUTION * j + i) * (VERTEX_SIZE);
				// VERTEX POSITION
				vertices[offset + 0] = x;
				vertices[offset + 1] = y;
				vertices[offset + 2] = z;
				// raw color
				vertices[offset + 3] = 0;
				vertices[offset + 4] = 0;
				vertices[offset + 5] = 0;
				//TEXTURE COORDINATES
				vertices[offset + 6] = texCoordinate.x;
				vertices[offset + 7] = texCoordinate.y;
				//NORMAL
				vertices[offset + 8] = normal.x;
				vertices[offset + 9] = normal.y;
				vertices[offset + 10] = normal.z;
				//TANGENT
				vertices[offset + 11] = -sin(theta) * cos(phi);
				vertices[offset + 12] = 0;
				vertices[offset + 13] = sin(theta) * cos(phi);
				//BITANGENT
				vertices[offset + 14] = cos(theta) * cos(phi);
				vertices[offset + 15] = -sin(theta);
				vertices[offset + 16] = cos(theta) * sin(phi);
			}
		for (int j = 0; j < GEOMETRY_RESOLUTION - 1; j++)
		{
			for (int k = 0; k < GEOMETRY_RESOLUTION; k++)
			{
				offset = (j * GEOMETRY_RESOLUTION + k);
				indices[offset * 6 + 0] = offset;
				indices[offset * 6 + 1] = offset + 1;
				indices[offset * 6 + 2] = offset + GEOMETRY_RESOLUTION;

				indices[offset * 6 + 3] = offset + 1;
				indices[offset * 6 + 4] = offset + GEOMETRY_RESOLUTION;
				indices[offset * 6 + 5] = offset + GEOMETRY_RESOLUTION + 1;
			}
			offset = (j * GEOMETRY_RESOLUTION + GEOMETRY_RESOLUTION - 1) * 6;
			indices[offset + 3] = (j * GEOMETRY_RESOLUTION);
			indices[offset + 4] = (j * GEOMETRY_RESOLUTION) + GEOMETRY_RESOLUTION;
			indices[offset + 5] = (j * GEOMETRY_RESOLUTION) + GEOMETRY_RESOLUTION - 1;
		}
	}
}