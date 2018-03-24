#pragma once
#include "Drawable.h"

namespace Drawable
{
	class Triangle
		: public cDrawable
	{
	public:
		Triangle(const glm::vec3 &position, GLuint programID);
		~Triangle();

	protected:
		static std::vector<glm::vec3> getPoints();
	};
}
