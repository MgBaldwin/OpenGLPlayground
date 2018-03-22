#pragma once
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
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
};

