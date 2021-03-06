#pragma once
#include <OpenGLWindow.h>

using namespace System;

namespace OpenGLWrapper {
	public ref class OpenGLWindowWrapper
		: public System::Windows::Forms::NativeWindow
	{
		OpenGLWindow *p_Window;

	public:
		OpenGLWindowWrapper();
		~OpenGLWindowWrapper();
		!OpenGLWindowWrapper();

		void Create(IntPtr handle);
		void Resize(int width, int height);
		void Draw();
	};
}
