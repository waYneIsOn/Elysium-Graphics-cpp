/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_SWAPCHAINDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_SWAPCHAINDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESWAPCHAIN
#include "../Elysium.Graphics/INativeSwapchain.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#include "IncludeDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API SwapchainDX12 final : public INativeSwapchain
	{
	public:
		SwapchainDX12(const SwapchainDX12& Source) = delete;
		SwapchainDX12(SwapchainDX12&& Right) noexcept = delete;
		virtual ~SwapchainDX12();

		virtual void AquireNextImage() override;
	private:
		SwapchainDX12();
	};
}
#endif
