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
	glfwSetWindowCloseCallback(_NativeWindow, WindowShouldCloseCallback);
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

	const Elysium::Core::Text::Encoding& ASCIIEncoding = Elysium::Core::Text::Encoding::ASCII();
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> TitleBytes = ASCIIEncoding.GetBytes(&_Title[0], _Title.GetLength(), 1);
	glfwSetWindowTitle(_NativeWindow, (const char*)&TitleBytes[0]);
}

void* Elysium::Graphics::Platform::GLFW::GLFWGameWindow::GetHandle() const
{
	return glfwGetWin32Window(_NativeWindow);
}

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::Show()
{
	Activated(this, Elysium::Core::EventArgs());
	glfwShowWindow(_NativeWindow);
	while (_NativeWindow != nullptr && !glfwWindowShouldClose(_NativeWindow))
	{
		glfwPollEvents();
		Paint(this, Elysium::Core::EventArgs());
	}
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

void Elysium::Graphics::Platform::GLFW::GLFWGameWindow::WindowShouldCloseCallback(GLFWwindow* window)
{
	glfwDestroyWindow(window);
}

GLFWwindow* Elysium::Graphics::Platform::GLFW::GLFWGameWindow::CreateNativeWindow(const Core::String& Title, const bool Fullscreen, const bool BorderlessWindow)
{
	const Elysium::Core::Text::Encoding& ASCIIEncoding = Elysium::Core::Text::Encoding::ASCII();
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> TitleBytes = ASCIIEncoding.GetBytes(&Title[0], Title.GetLength(), 1);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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
