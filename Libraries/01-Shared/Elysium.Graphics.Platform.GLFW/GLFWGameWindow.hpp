/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_GLFW_GLFWGAMEWINDOW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_PLATFORM_GLFW_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PLATFORM_CANVAS
#include "../Elysium.Graphics/Canvas.hpp"
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef _glfw3_h_
#include "../../../../GLFW/glfw-3.3.2/include/GLFW/glfw3.h"
#endif

namespace Elysium::Graphics::Platform::GLFW
{
	class ELYSIUM_GRAPHICS_PLATFORM_GLFW_API GLFWGameWindow final : public Canvas
	{
	public:
		GLFWGameWindow();
		GLFWGameWindow(const GLFWGameWindow& Source) = delete;
		GLFWGameWindow(GLFWGameWindow&& Right) noexcept = delete;
		virtual ~GLFWGameWindow();

		GLFWGameWindow& operator=(const GLFWGameWindow& Source) = delete;
		GLFWGameWindow& operator=(GLFWGameWindow&& Right) noexcept = delete;

		virtual const Core::Math::Geometry::Rectangle& GetClientBounds() const override;
		virtual void* GetHandle() const override;
		virtual const Platform::DisplayOrientation GetDisplayOrientation() const override;
		virtual const Core::String& GetTitle() const override;

		virtual void SetTitle(const Core::String& Value) override;

		virtual void Show() override;
		virtual void Close() override;
	private:
		static const DisplayOrientation _DisplayOrientation = DisplayOrientation::Default;

		Core::String _Title = u8"Elysium Graphics :: GLFWGameWindow";
		Core::Math::Geometry::Rectangle _ClientBounds = Core::Math::Geometry::Rectangle();
		GLFWmonitor* _PrimaryMonitor;
		const GLFWvidmode* _VidMode;
		GLFWwindow* _NativeWindow;

		GLFWmonitor* GetPrimaryMonitor();
		GLFWwindow* CreateNativeWindow(const Core::String& Title, const bool Fullscreen, const bool BorderlessWindow);

		static void Window_ShouldCloseCallback(GLFWwindow* Window);

		static void Window_FocusCallback(GLFWwindow* Window, int HasActivated);

		static void Window_SizeCallback(GLFWwindow* Window, int Width, int Height);
	};
}
#endif
