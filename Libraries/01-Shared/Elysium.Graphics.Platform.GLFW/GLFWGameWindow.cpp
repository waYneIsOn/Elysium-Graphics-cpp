#include "GLFWGameWindow.hpp"

#ifndef _glfw3_native_h_
#define GLFW_EXPOSE_NATIVE_WIN32
#include "../../../../GLFW/glfw-3.3.2/include/GLFW/glfw3native.h"
#endif

#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#include "../Elysium.Graphics/GraphicsDeviceManager.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"
#endif

Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GLFWGameWindow()
	: Elysium::Graphics::Platform::Canvas(),
	_PrimaryMonitor(GetPrimaryMonitor()), _VidMode(glfwGetVideoMode(_PrimaryMonitor)), _NativeWindow(CreateNativeWindow(_Title, false, false))
{
	glfwSetWindowUserPointer(_NativeWindow, static_cast<void*>(this));

	//glfwSetMonitorCallback

	glfwSetWindowCloseCallback(_NativeWindow, Window_ShouldCloseCallback);
	//glfwSetWindowContentScaleCallback
	glfwSetWindowFocusCallback(_NativeWindow, Window_FocusCallback);
	//glfwSetWindowIconifyCallback
	//glfwSetWindowMaximizeCallback - no need to use this as a resize will be called when maximizing

	//glfwSetWindowPosCallback
	//glfwSetWindowRefreshCallback

	glfwGetWindowFrameSize(_NativeWindow, &_ClientBounds.X, &_ClientBounds.Y, &_ClientBounds.Width, &_ClientBounds.Height);
}
Elysium::Graphics::Platform::GLFW::GLFWGameWindow::~GLFWGameWindow()
{
	Close();
	_VidMode = nullptr;
	_PrimaryMonitor = nullptr;
	glfwTerminate();
}

const Elysium::Core::Math::Geometry::Rectangle& Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetClientBounds() const
{
	return _ClientBounds;
}

void* Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetHandle() const
{
	return glfwGetWin32Window(_NativeWindow);
}

const Elysium::Graphics::Platform::DisplayOrientation Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetDisplayOrientation() const
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

	const Elysium::Core::Text::Encoding& ASCIIEncoding = Elysium::Core::Text::Encoding::ASCII();
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> TitleBytes = ASCIIEncoding.GetBytes(&_Title[0], _Title.GetLength(), 1);
	glfwSetWindowTitle(_NativeWindow, (const char*)&TitleBytes[0]);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Show()
{
	Activated(this, Elysium::Core::EventArgs());
	glfwShowWindow(_NativeWindow);
	glfwSetWindowSizeCallback(_NativeWindow, Window_SizeCallback);
	while (_NativeWindow != nullptr && !glfwWindowShouldClose(_NativeWindow))
	{
		glfwPollEvents();
		Paint(this, Elysium::Core::EventArgs());
	}
	glfwSetWindowSizeCallback(_NativeWindow, nullptr);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Close()
{
	if (_NativeWindow != nullptr)
	{
		Exiting(this, Elysium::Core::EventArgs());
		glfwSetWindowShouldClose(_NativeWindow, GLFW_TRUE);
		while (!glfwWindowShouldClose(_NativeWindow))
		{ }
		_NativeWindow = nullptr;
	}
}

GLFWmonitor* Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetPrimaryMonitor()
{
	glfwInit();
	return glfwGetPrimaryMonitor();
}

GLFWwindow* Elysium::Graphics::Platform::GLFW::GLFWGameWindow::CreateNativeWindow(const Core::String& Title, const bool Fullscreen, const bool BorderlessWindow)
{
	const Elysium::Core::Text::Encoding& ASCIIEncoding = Elysium::Core::Text::Encoding::ASCII();
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> TitleBytes = ASCIIEncoding.GetBytes(&Title[0], Title.GetLength(), 1);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	if (Fullscreen)
	{
		if (BorderlessWindow)
		{
			glfwWindowHint(GLFW_RED_BITS, _VidMode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, _VidMode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, _VidMode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, _VidMode->refreshRate);
		}
		return glfwCreateWindow(_VidMode->width, _VidMode->height, (const char*)&TitleBytes[0], _PrimaryMonitor, nullptr);
	}
	else
	{
		GLFWwindow* Window = glfwCreateWindow(GraphicsDeviceManager::DefaultBackBufferWidth, GraphicsDeviceManager::DefaultBackBufferHeight, (const char*)&TitleBytes[0], nullptr, nullptr);
		glfwSetWindowPos(Window, _VidMode->width / 2 - GraphicsDeviceManager::DefaultBackBufferWidth / 2, _VidMode->height / 2 - GraphicsDeviceManager::DefaultBackBufferHeight / 2);

		return Window;
	}
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Window_ShouldCloseCallback(GLFWwindow* window)
{
	glfwDestroyWindow(window);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Window_FocusCallback(GLFWwindow* Window, int HasActivated)
{
	GLFWGameWindow* Handler = static_cast<GLFWGameWindow*>(glfwGetWindowUserPointer(Window));
	HasActivated == GLFW_TRUE ? Handler->Activated(Handler, Elysium::Core::EventArgs()) : Handler->Deactivated(Handler, Elysium::Core::EventArgs());
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Window_SizeCallback(GLFWwindow* Window, int Width, int Height)
{
	GLFWGameWindow* Handler = static_cast<GLFWGameWindow*>(glfwGetWindowUserPointer(Window));
	Handler->_ClientBounds.Width = Width;
	Handler->_ClientBounds.Height = Height;

	Elysium::Graphics::Platform::SizeChangedEventArgs EventArgs = Elysium::Graphics::Platform::SizeChangedEventArgs(Width, Height);
	Handler->SizeChanged(Handler, EventArgs);
}
