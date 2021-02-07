/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_PRESENTATIONPARAMETERS
#define ELYSIUM_GRAPHICS_RENDERING_PRESENTATIONPARAMETERS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PLATFORM_CANVAS
#include "Canvas.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#include "GraphicsDeviceManager.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API PresentationParameters
	{
	public:
		PresentationParameters(Platform::Canvas& Canvas);
		PresentationParameters(const PresentationParameters& Source) = delete;
		PresentationParameters(PresentationParameters&& Right) noexcept = delete;
		virtual ~PresentationParameters();

		PresentationParameters& operator=(const PresentationParameters& Source) = delete;
		PresentationParameters& operator=(PresentationParameters&& Right) noexcept = delete;

		Platform::Canvas& GetCanvas() const;
		const Elysium::Core::uint32_t GetBackBufferWidth() const;
		const Elysium::Core::uint32_t GetBackBufferHeight() const;
		const Elysium::Core::uint32_t GetBackBufferCount() const;

		void SetBackBufferWidth(const Elysium::Core::uint32_t Value);
		void SetBackBufferHeight(const Elysium::Core::uint32_t Value);
		void SetBackBufferCount(const Elysium::Core::uint32_t Value);
	protected:
		Platform::Canvas& _Canvas;
		Elysium::Core::uint32_t _BackBufferWidth = GraphicsDeviceManager::DefaultBackBufferWidth;
		Elysium::Core::uint32_t _BackBufferHeight = GraphicsDeviceManager::DefaultBackBufferHeight;
		Elysium::Core::uint32_t _BackBufferCount = GraphicsDeviceManager::DefaultBackBufferCount;
	};
}
#endif
