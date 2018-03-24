#include "stdafxNative.h"
#include "OpenGLWindow.h"

#include <assert.h>

PIXELFORMATDESCRIPTOR OpenGLWindow::s_Pfd =					// pfd Tells Windows How We Want Things To Be
{
	sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
	1,											// Version Number
	PFD_DRAW_TO_WINDOW |						// Format Must Support Window
	PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
	PFD_DOUBLEBUFFER,							// Must Support Double Buffering
	PFD_TYPE_RGBA,								// Request An RGBA Format
	16,											// Select Our Color Depth
	0, 0, 0, 0, 0, 0,							// Color Bits Ignored
	0,											// No Alpha Buffer
	0,											// Shift Bit Ignored
	0,											// No Accumulation Buffer
	0, 0, 0, 0,									// Accumulation Bits Ignored
	16,											// 16Bit Z-Buffer (Depth Buffer)  
	0,											// No Stencil Buffer
	0,											// No Auxiliary Buffer
	PFD_MAIN_PLANE,								// Main Drawing Layer
	0,											// Reserved
	0, 0, 0										// Layer Masks Ignored
};

OpenGLWindow::OpenGLWindow()
	: m_Handle(NULL)
	, m_HRC(NULL)
{
}


OpenGLWindow::~OpenGLWindow()
{
	KillGLWindow();
}

void OpenGLWindow::Resize(int width, int height)		// Resize And Initialize The GL Window
{
	if (height == 0)									// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	m_Registry.SetPerspective(glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f));
}

void OpenGLWindow::InitGL()										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LESS);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glewInit();
}

void OpenGLWindow::Draw()								// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	
	m_Registry.Draw();

	auto hDC = GetDC(m_Handle);
	SwapBuffers(hDC);
	ReleaseDC(m_Handle, hDC);
}

void OpenGLWindow::KillGLWindow()				// Properly Kill The Window
{
	if (m_HRC)									// Do We Have A Rendering Context?
	{
		auto results = wglMakeCurrent(NULL, NULL);
		assert(results);		// Are We Able To Release The DC And RC Contexts?
		results = wglDeleteContext(m_HRC);
		assert(results);		// Are We Able To Delete The RC?
		m_HRC = NULL;							// Set RC To NULL
	}
}

void OpenGLWindow::Create(HWND handle)
{
	m_Handle = handle;
	auto hDC = GetDC(m_Handle);
	assert(hDC);										// Did We Get A Device Context?

	auto pixelFormat = ChoosePixelFormat(hDC, &s_Pfd);
	assert(pixelFormat);								// Did Windows Find A Matching Pixel Format?

	auto results = SetPixelFormat(hDC, pixelFormat, &s_Pfd);
	assert(results);									// Are We Able To Set The Pixel Format?

	m_HRC = wglCreateContext(hDC);
	assert(m_HRC);										// Are We Able To Get A Rendering Context?

	results = wglMakeCurrent(hDC, m_HRC);
	assert(results);									// Try To Activate The Rendering Context

	ReleaseDC(m_Handle, hDC);

	InitGL();											// Initialize Our Newly Created GL Window

	m_Registry.SetView(glm::lookAt(
		glm::vec3(0.0f, 0.0f, 6.0f),		//Camera is at (0, 0, 2)
		glm::vec3(0.0f, 0.0f, 0.0f),		//and looking at the origin
		glm::vec3(0.0f, -1.0f, 0.0f)		//head is up
	));

	auto triangle = m_Registry.CreateTriangle(glm::vec3(0.0f, 0.5f, 0.0f));
	auto triangleB = m_Registry.CreateTriangle(glm::vec3(0.0f, -1.0f, 0.0f));
	m_Registry.Buffer(triangle);
	m_Registry.Buffer(triangleB);
}
