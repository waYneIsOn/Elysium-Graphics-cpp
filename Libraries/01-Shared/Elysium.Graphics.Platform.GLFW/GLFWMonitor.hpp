/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_GLFW_GLFWMONITOR
#define ELYSIUM_GRAPHICS_PLATFORM_GLFW_GLFWMONITOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PLATFORM_GLFW_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PLATFORM_IMONITOR
#include "../Elysium.Graphics/IMonitor.hpp"
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef _glfw3_h_
#include "../../../../GLFW/glfw-3.3.2/include/GLFW/glfw3.h"
#endif

namespace Elysium::Graphics::Platform::GLFW
{
	class GLFWGameWindow;

	class ELYSIUM_GRAPHICS_PLATFORM_GLFW_API GLFWMonitor final : public IMonitor
	{
		friend class GLFWGameWindow;
	public:
		GLFWMonitor();
		GLFWMonitor(const GLFWMonitor& Source) = delete;
		GLFWMonitor(GLFWMonitor&& Right) noexcept = delete;
		virtual ~GLFWMonitor();

		GLFWMonitor& operator=(const GLFWMonitor& Source) = delete;
		GLFWMonitor& operator=(GLFWMonitor&& Right) noexcept = delete;

		virtual const void* GetHandle() const override;
		virtual const bool GetIsPrimaryMonitor() const override;
		virtual const Elysium::Core::String GetName() const override;
		virtual const Elysium::Core::Math::Geometry::Point& GetPhysicalSize() const override;
		virtual const Elysium::Core::Math::Geometry::Point& GetCurrentResolution() const override;
		virtual const Elysium::Core::uint32_t GetCurrentRefreshRate() const override;
		virtual const Elysium::Core::Math::Geometry::Point& GetPosition() const override;

		static const Elysium::Core::Collections::Template::Array<GLFWMonitor> GetMonitors();
	private:
		GLFWmonitor* _NativeMonitor;
		const GLFWvidmode* _NativeVideoMode;
		Elysium::Core::Math::Geometry::Point _PhysicalSize;
		Elysium::Core::Math::Geometry::Point _CurrentResolution;
		Elysium::Core::Math::Geometry::Point _Position;

		//static Elysium::Core::Collections::Template::Array<GLFWMonitor> _GLFWMonitors;

		void SetNativeMonitor(GLFWmonitor* NativeMonitor);

		static void Monitor_Callback(GLFWmonitor* NativeMonitor, Elysium::Core::int32_t Event);
	};
}
#endif
