/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_GRAPHICSINSTANCEDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_GRAPHICSINSTANCEDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSAPI
#include "../Elysium.Graphics/INativeGraphicsAPI.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#include "IncludeDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PHYSICALDEVICEDX12
#include "PhysicalDeviceDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PRESENTATIONPARAMETERSDX12
#include "PresentationParametersDx12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_SURFACEDX12
#include "SurfaceDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API GraphicsInstanceDX12 final : public INativeGraphicsAPI
	{
	public:
		GraphicsInstanceDX12();
		GraphicsInstanceDX12(const GraphicsInstanceDX12& Source) = delete;
		GraphicsInstanceDX12(GraphicsInstanceDX12&& Right) noexcept = delete;
		virtual ~GraphicsInstanceDX12();

		GraphicsInstanceDX12& operator=(const GraphicsInstanceDX12& Source) = delete;
		GraphicsInstanceDX12& operator=(GraphicsInstanceDX12&& Right) noexcept = delete;

		const Core::Collections::Template::Array<PhysicalDeviceDX12> GetPhysicalGraphicsDevices();

		void EnableDebugging();
		void DisableDebugging();

		void Initialize(const PresentationParametersDX12& PresentationParameters);
	private:
		IDXGIFactory2* _Factory;
		ID3D12Debug* _Debug;
	};
}
#endif
