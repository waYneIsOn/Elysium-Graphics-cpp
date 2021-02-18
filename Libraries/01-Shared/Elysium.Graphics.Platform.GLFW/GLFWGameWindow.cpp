#include "GLFWGameWindow.hpp"

#ifndef ELYSIUM_GRAPHICS_APINOTAVAILABLEEXCEPTION
#include "../Elysium.Graphics/APINotAvailableException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#include "../Elysium.Graphics/GraphicsDeviceManager.hpp"
#endif

#ifndef _glfw3_native_h_
#define GLFW_EXPOSE_NATIVE_WIN32
#include "../../../../GLFW/glfw-3.3.2/include/GLFW/glfw3native.h"
#endif

Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GLFWGameWindow(const GLFWMonitor& Monitor)
	: Elysium::Graphics::Platform::Canvas(),
	_Monitor(Monitor), _NativeWindow(CreateNativeWindow(_Title, false, false)),
	_IsMinimized(false)
{
	glfwSetWindowUserPointer(_NativeWindow, static_cast<void*>(this));
	glfwGetWindowFrameSize(_NativeWindow, &_ClientBounds.X, &_ClientBounds.Y, &_ClientBounds.Width, &_ClientBounds.Height);
}
Elysium::Graphics::Platform::GLFW::GLFWGameWindow::~GLFWGameWindow()
{
	Close();
	if (_NativeWindow != nullptr)
	{
		glfwDestroyWindow(_NativeWindow);
		_NativeWindow = nullptr;
	}
	glfwTerminate();
}

const bool Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetIsMinimized() const
{
	return _IsMinimized;
}

const Elysium::Core::Math::Geometry::Rectangle& Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetClientBounds() const
{
	return _ClientBounds;
}

void* Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetHandle() const
{
	return glfwGetWin32Window(_NativeWindow);
}

const Elysium::Graphics::DisplayOrientation Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetDisplayOrientation() const
{
	return _DisplayOrientation;
}

const Elysium::Core::String& Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetTitle() const
{
	return _Title;
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::SetTitle(const Core::String& Value)
{
	_Title = Value;
	glfwSetWindowTitle(_NativeWindow, (const char*)&_Title[0]);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Show()
{
	glfwShowWindow(_NativeWindow);

	//glfwSetMonitorCallback

	glfwSetWindowCloseCallback(_NativeWindow, Window_ShouldCloseCallback);
	//glfwSetWindowContentScaleCallback
	glfwSetWindowFocusCallback(_NativeWindow, Window_FocusCallback);
	glfwSetWindowIconifyCallback(_NativeWindow, Window_IconifyCallback);
	//glfwSetWindowMaximizeCallback - no need to use this as a resize will be called when maximizing
	glfwSetWindowSizeCallback(_NativeWindow, Window_SizeCallback);

	//glfwSetWindowPosCallback
	//glfwSetWindowRefreshCallback

	while (_NativeWindow != nullptr && !glfwWindowShouldClose(_NativeWindow))
	{
		glfwPollEvents();
		Paint(this);
	}
	//glfwSetWindowSizeCallback(_NativeWindow, nullptr);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Close()
{
	if (_NativeWindow != nullptr)
	{
		Exiting(this);
		glfwSetWindowShouldClose(_NativeWindow, GLFW_TRUE);
		while (!glfwWindowShouldClose(_NativeWindow))
		{ }
		_NativeWindow = nullptr;
	}
}

GLFWwindow* Elysium::Graphics::Platform::GLFW::GLFWGameWindow::CreateNativeWindow(const Core::String& Title, const bool Fullscreen, const bool BorderlessWindow)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	if (Fullscreen)
	{
		if (BorderlessWindow)
		{
			glfwWindowHint(GLFW_RED_BITS, _Monitor._NativeVideoMode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, _Monitor._NativeVideoMode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, _Monitor._NativeVideoMode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, _Monitor._NativeVideoMode->refreshRate);
		}
		return glfwCreateWindow(_Monitor._NativeVideoMode->width, _Monitor._NativeVideoMode->height, (const char*)&Title[0], _Monitor._NativeMonitor, nullptr);
	}
	else
	{
		GLFWwindow* Window = glfwCreateWindow(GraphicsDeviceManager::DefaultBackBufferWidth, GraphicsDeviceManager::DefaultBackBufferHeight, (const char*)&Title[0], nullptr, nullptr);
		CenterToMonitor(Window);
		return Window;
	}
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::CenterToMonitor(GLFWwindow* Window)
{
	glfwSetWindowPos(Window, _Monitor._Position.X + _Monitor._NativeVideoMode->width / 2 - GraphicsDeviceManager::DefaultBackBufferWidth / 2,
		_Monitor._Position.Y + _Monitor._NativeVideoMode->height / 2 - GraphicsDeviceManager::DefaultBackBufferHeight / 2);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Window_ShouldCloseCallback(GLFWwindow* Window)
{
	GLFWGameWindow* Handler = static_cast<GLFWGameWindow*>(glfwGetWindowUserPointer(Window));
	Handler->Close();
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Window_IconifyCallback(GLFWwindow* Window, int Iconified)
{
	GLFWGameWindow* Handler = static_cast<GLFWGameWindow*>(glfwGetWindowUserPointer(Window));
	Handler->_IsMinimized = Iconified == 1;
	Iconified == 1 ? Handler->Suspend(Handler) : Handler->Resume(Handler);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Window_FocusCallback(GLFWwindow* Window, int HasReceivedFocus)
{
	GLFWGameWindow* Handler = static_cast<GLFWGameWindow*>(glfwGetWindowUserPointer(Window));
	Handler->FocusChanged(Handler, HasReceivedFocus);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Window_SizeCallback(GLFWwindow* Window, int Width, int Height)
{
	GLFWGameWindow* Handler = static_cast<GLFWGameWindow*>(glfwGetWindowUserPointer(Window));
	Handler->_ClientBounds.Width = Width;
	Handler->_ClientBounds.Height = Height;

	Elysium::Graphics::Platform::SizeChangedEventArgs EventArgs = Elysium::Graphics::Platform::SizeChangedEventArgs(Width, Height);
	Handler->SizeChanged(Handler, EventArgs);
}
