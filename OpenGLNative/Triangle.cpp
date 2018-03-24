#include "stdafxNative.h"
#include "Triangle.h"

namespace Drawable
{
	Triangle::Triangle(const glm::vec3 &position, GLuint programID)
		: cDrawable(position, programID, getPoints())
	{

	}

	Triangle::~Triangle()
	{

	}

	std::vector<glm::vec3> Triangle::getPoints()
	{
		glm::vec3 arr[] = { {  0.0f,  0.0f,  0.0f},
							{  1.0f,  1.0f,  0.0f},
							{ -1.0f,  1.0f,  0.0f}};

		return std::vector<glm::vec3>(arr, arr + 3);
	}
}
