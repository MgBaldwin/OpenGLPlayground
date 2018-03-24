#include "stdafxNative.h"
#include "DrawableRegistry.h"

#include "Triangle.h"

namespace Registry
{
	DrawableRegistry::DrawableRegistry()
		: m_ProgramID(NULL)
	{
	}

	DrawableRegistry::~DrawableRegistry()
	{
		if (m_ProgramID)
			glDeleteProgram(m_ProgramID);
	}

	UINT DrawableRegistry::CreateTriangle(const glm::vec3 &position)
	{
		auto ID = getNextID();

		m_Drawables.emplace(ID, std::make_unique<Drawable::Triangle>(position, getShader()));
		return ID;
	}

	void DrawableRegistry::Buffer(UINT ID)
	{
		auto drawable = m_Drawables.find(ID);
		assert(drawable != m_Drawables.cend());

		drawable->second->Buffer();
	}

	void DrawableRegistry::Draw()
	{
		auto VP = m_PerspectiveMatrix * m_ViewMatrix;
		for (auto &drawable : m_Drawables)
			drawable.second->Draw(VP);
	}

	void DrawableRegistry::SetPerspective(const glm::mat4 &perspectiveMatrix)
	{
		m_PerspectiveMatrix = perspectiveMatrix;
	}

	void DrawableRegistry::SetView(const glm::mat4 &viewMatrix)
	{
		m_ViewMatrix = viewMatrix;
	}

	UINT DrawableRegistry::getNextID()
	{
		auto idealID = 0u;
		for (; m_Drawables.find(idealID) != m_Drawables.cend(); idealID++);

		return idealID;
	}

	UINT DrawableRegistry::getShader()
	{
		if (!m_ProgramID)
		{
			const char* vertex_shader =
				"#version 450\n"
				"layout(location = 0) in vec3 vp;"
				"uniform mat4 MVP;"
				"void main() {"
				"  gl_Position = MVP * vec4(vp, 1.0);"
				"}";

			const char* fragment_shader =
				"#version 450\n"
				"out vec4 frag_colour;"
				"void main() {"
				"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
				"}";

			GLuint vs = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vs, 1, &vertex_shader, NULL);
			glCompileShader(vs);
			GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fs, 1, &fragment_shader, NULL);
			glCompileShader(fs);

			m_ProgramID = glCreateProgram();
			glAttachShader(m_ProgramID, fs);
			glAttachShader(m_ProgramID, vs);
			glLinkProgram(m_ProgramID);

			glDetachShader(m_ProgramID, vs);
			glDetachShader(m_ProgramID, fs);

			glDeleteShader(vs);
			glDeleteShader(fs);
		}

		return m_ProgramID;
	}
}
