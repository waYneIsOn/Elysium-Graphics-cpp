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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_QUEUEDX12
#include "QueueDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API SwapchainDX12 final : public INativeSwapchain
	{
	public:
		SwapchainDX12(const LogicalDeviceDX12& LogicalDevice, const QueueDX12& DirectQueue);
		SwapchainDX12(const SwapchainDX12& Source) = delete;
		SwapchainDX12(SwapchainDX12&& Right) noexcept = delete;
		virtual ~SwapchainDX12();

		virtual const Elysium::Core::uint32_t GetBackBufferImageCount() const override;

		virtual void Recreate() override;
		virtual void AquireNextImage(const INativeSemaphore& PresentSemaphore, const Elysium::Core::uint64_t Timeout) override;
		virtual void PresentFrame(const INativeSemaphore& RenderSemaphore, const INativeQueue& PresentationQueue) override;
	private:
		const LogicalDeviceDX12& _LogicalDevice;
		const QueueDX12& _DirectQueue;
		IDXGISwapChain* _NativeSwapchain;
		//IDXGISwapChain4* _NativeSwapchain;
	};
}
#endif
