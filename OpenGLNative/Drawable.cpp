#include "stdafxNative.h"
#include "Drawable.h"

namespace Drawable
{
	cDrawable::cDrawable(const glm::vec3 &position, GLuint programID, const std::vector<glm::vec3> &vertices)
		: m_ProgramID(programID)
		, m_Vertices(vertices)
		, m_Vao(0)
		, m_Vbo(0)
		, m_ModelMatrix(glm::translate(position))
	{
		glGenVertexArrays(1, &m_Vao);
		glGenBuffers(1, &m_Vbo);
	}

	cDrawable::~cDrawable()
	{
		glDeleteVertexArrays(1, &m_Vao);
		glDeleteBuffers(1, &m_Vbo);
	} 

	void cDrawable::Buffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec3), &m_Vertices[0], GL_STATIC_DRAW);

		glBindVertexArray(m_Vao);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	void cDrawable::Draw(const glm::mat4 &VP)
	{
		auto MVP = VP * m_ModelMatrix;

		GLuint MatrixID = glGetUniformLocation(m_ProgramID, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glUseProgram(m_ProgramID);
		glBindVertexArray(m_Vao);

		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_Vertices.size());
	}

	void cDrawable::Translate(const glm::vec3 &translationVector)
	{
		m_ModelMatrix *= glm::translate(translationVector);
	}
}
