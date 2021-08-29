/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#define ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_DISPLAYMODE
#include "DisplayMode.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#include "GraphicsDeviceManager.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#include "../Elysium.Graphics.Presentation/Control.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_DISPLAYDEVICE
#include "../Elysium.Graphics.Presentation/DisplayDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTMODE
#include "PresentMode.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DEPTHFORMAT
#include "DepthFormat.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSAPI
#include "INativeGraphicsAPI.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SURFACEFORMAT
#include "SurfaceFormat.hpp"
#endif

namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API PresentationParameters
	{
	public:
		PresentationParameters(Rendering::Native::INativeGraphicsAPI& NativeGraphicsAPI, Presentation::Control& Canvas);
		PresentationParameters(const PresentationParameters& Source) = delete;
		PresentationParameters(PresentationParameters&& Right) noexcept = delete;
		virtual ~PresentationParameters();

		PresentationParameters& operator=(const PresentationParameters& Source) = delete;
		PresentationParameters& operator=(PresentationParameters&& Right) noexcept = delete;

		const Elysium::Graphics::DisplayMode GetDisplayMode() const;
		const Elysium::Graphics::Presentation::DisplayDevice& GetDisplayDevice() const;
		const Elysium::Graphics::Rendering::Native::INativePhysicalDevice& GetPhysicalDevice() const;
		Presentation::Control& GetCanvas() const;
		const Elysium::Core::uint32_t GetRenderResolution() const;
		const Elysium::Core::uint32_t GetBackBufferWidth() const;
		const Elysium::Core::uint32_t GetBackBufferHeight() const;
		const Elysium::Core::uint32_t GetBackBufferCount() const;
		const Elysium::Graphics::PresentMode GetPresentMode() const;
		const Rendering::SurfaceFormat GetDesiredSurfaceFormat() const;
		const Rendering::DepthFormat GetDesiredDepthFormat() const;

		void SetDisplayMode(const Elysium::Graphics::DisplayMode Value);
		void SetDisplayDeviceIndex(const Elysium::Core::uint32_t Value);
		void SetGraphicsDeviceIndex(const Elysium::Core::uint32_t Value);
		void SetPresentMode(const Elysium::Graphics::PresentMode Value);
		void SetRenderResolution(const Elysium::Core::uint32_t Value);
		void SetBackBufferWidth(const Elysium::Core::uint32_t Value);
		void SetBackBufferHeight(const Elysium::Core::uint32_t Value);
		void SetBackBufferCount(const Elysium::Core::uint32_t Value);
		void SetDesiredSurfaceFormat(const Rendering::SurfaceFormat Value);
		void SetDesiredDepthFormat(const Rendering::DepthFormat Value);
	protected:
		// graphics api
		Rendering::Native::INativeGraphicsAPI& _NativeGraphicsAPI;
		Presentation::Control& _Canvas;

		// display parameters
		DisplayMode _DisplayMode = DisplayMode::Windowed;
		Elysium::Core::uint32_t _DisplayDeviceIndex = 0;
		Elysium::Core::uint32_t _GraphicsDeviceIndex = 0;
		Elysium::Core::uint32_t _RenderResolution = 100;
		PresentMode _PresentMode = PresentMode::VerticalSync;

		// swapchain & depthbuffer related parameters
		Elysium::Core::uint32_t _BackBufferWidth = GraphicsDeviceManager::DefaultBackBufferWidth;
		Elysium::Core::uint32_t _BackBufferHeight = GraphicsDeviceManager::DefaultBackBufferHeight;
		Elysium::Core::uint32_t _BackBufferCount = GraphicsDeviceManager::DefaultBackBufferCount;
		Rendering::SurfaceFormat _DesiredSurfaceFormat = Rendering::SurfaceFormat::B8G8R8A8_sRGB;
		Rendering::DepthFormat _DesiredDepthFormat = Rendering::DepthFormat::Depth32Stencil8;

		// ...
		Elysium::Core::uint32_t _GameFramerateLimit = 240;
		Elysium::Core::uint32_t _MenuFramerateLimit = 60;
		Elysium::Core::uint32_t _InactiveFramerateLimit = 15;
	};
}
#endif
