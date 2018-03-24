#pragma once
#include "Drawable.h"

namespace Registry
{
	class DrawableRegistry
	{
	public:
		DrawableRegistry();
		~DrawableRegistry();

		UINT CreateTriangle(const glm::vec3 &position);

		void Buffer(UINT ID);
		void Draw();

		void SetPerspective(const glm::mat4 &perspectiveMatrix);
		void SetView(const glm::mat4 &viewMatrix);
	private:
		UINT getNextID();

		UINT getShader();

		GLuint m_ProgramID;

		std::unordered_map<UINT, std::unique_ptr<Drawable::cDrawable>> m_Drawables;
	
		glm::mat4 m_PerspectiveMatrix;
		glm::mat4 m_ViewMatrix;
	};
}
