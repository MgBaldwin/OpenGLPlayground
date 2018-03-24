#pragma once

namespace Drawable
{
	class cDrawable
	{
	public:
		virtual ~cDrawable();
		
		void Buffer();
		void Draw(const glm::mat4 &VP);

		void Translate(const glm::vec3 &translationVector);
	protected:
		cDrawable(const glm::vec3 &position, GLuint programID, const std::vector<glm::vec3> &vertices);

		//Variables
		std::vector<glm::vec3> m_Vertices;

		GLuint m_Vbo;
		GLuint m_Vao;
		GLuint m_ProgramID;

		glm::mat4 m_ModelMatrix;
	};
}
