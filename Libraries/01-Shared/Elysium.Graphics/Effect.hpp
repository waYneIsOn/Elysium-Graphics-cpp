/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_GRAPHICS_RENDERING_EFFECT
#define ELYSIUM_GRAPHICS_RENDERING_EFFECT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_BINARYREADER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/BinaryReader.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API Effect
	{
	public:
		Effect(const GraphicsDevice& GraphicsDevice, Elysium::Core::IO::BinaryReader& InputReader) noexcept;
		Effect(const Effect& Source) noexcept = delete;
		Effect(Effect&& Right) noexcept = delete;
		virtual ~Effect();

		Effect& operator=(const Effect& Source) noexcept = delete;
		Effect& operator=(Effect&& Right) noexcept = delete;
	private:

	};
}
#endif
