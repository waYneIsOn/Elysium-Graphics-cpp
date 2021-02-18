/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
/*
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_SURFACEDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_SURFACEDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#include "IncludeDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class GraphicsInstanceDX12;

	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API SurfaceDX12 final
	{
		friend class GraphicsInstanceDX12;
	public:
		SurfaceDX12(const SurfaceDX12& Source) = delete;
		SurfaceDX12(SurfaceDX12&& Right) noexcept = delete;
		virtual ~SurfaceDX12();
	private:
		SurfaceDX12();

		IDXGISurface2* _NativeSurface;
	};
}
#endif
*/