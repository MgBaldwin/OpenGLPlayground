#include "stdafxWrapper.h"

#include "OpenGLWrapper.h"

namespace OpenGLWrapper
{
	OpenGLWindowWrapper::OpenGLWindowWrapper()
	{
		p_Window = new OpenGLWindow();
	}

	OpenGLWindowWrapper::~OpenGLWindowWrapper()
	{
		this->!OpenGLWindowWrapper();
	}

	OpenGLWindowWrapper::!OpenGLWindowWrapper()
	{
		delete p_Window;
	}
	void OpenGLWindowWrapper::Create(IntPtr handle)
	{
		AssignHandle(handle);
		p_Window->Create((HWND)handle.ToPointer());
	}

	void OpenGLWindowWrapper::Resize(int width, int height)
	{
		p_Window->Resize(width, height);
	}

	void OpenGLWindowWrapper::Draw()
	{
		p_Window->Draw();
	}

}
