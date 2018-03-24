#pragma once
#include "DrawableRegistry.h"

class OpenGLWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();


	void Create(HWND handle);
	void Resize(int width, int height);
	void InitGL();
	void Draw();
	void KillGLWindow();
	
private:
	static PIXELFORMATDESCRIPTOR s_Pfd;

	HWND m_Handle;
	HGLRC m_HRC;

	Registry::DrawableRegistry m_Registry;
};

