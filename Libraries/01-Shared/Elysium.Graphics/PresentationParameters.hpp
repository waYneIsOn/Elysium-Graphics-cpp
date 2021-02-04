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

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API PresentationParameters
	{
	public:
		PresentationParameters(const Platform::Canvas& Canvas);
		PresentationParameters(const PresentationParameters& Source) = delete;
		PresentationParameters(PresentationParameters&& Right) noexcept = delete;
		virtual ~PresentationParameters();

		PresentationParameters& operator=(const PresentationParameters& Source) = delete;
		PresentationParameters& operator=(PresentationParameters&& Right) noexcept = delete;

		const Platform::Canvas& GetCanvas() const;

		virtual void Bla() = 0;
	private:
		const Platform::Canvas& _Canvas;
		Core::uint32_t _BackBufferWidth = 800;
		Core::uint32_t _BackBufferHeight = 460;
	};
}
#endif
