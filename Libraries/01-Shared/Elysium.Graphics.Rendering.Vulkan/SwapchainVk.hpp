/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESWAPCHAIN
#include "../Elysium.Graphics/INativeSwapchain.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class CommandBufferVk;
	class FramebufferVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SwapchainVk final : public INativeSwapchain
	{
		friend class CommandBufferVk;
		friend class FramebufferVk;
	public:
		SwapchainVk(SurfaceVk& Surface, const LogicalDeviceVk& LogicalDevice);
		SwapchainVk(const SwapchainVk& Source) = delete;
		SwapchainVk(SwapchainVk&& Right) noexcept = delete;
		virtual ~SwapchainVk();

		SwapchainVk& operator=(const SwapchainVk& Source) = delete;
		SwapchainVk& operator=(SwapchainVk&& Right) noexcept = delete;

		virtual const Elysium::Core::uint32_t GetBackBufferImageCount() const override;

		virtual void AquireNextImage(const INativeSemaphore& PresentSemaphore, const Elysium::Core::uint64_t Timeout) override;
		virtual void PresentFrame(const INativeSemaphore& RenderSemaphore, const INativeQueue& PresentationQueue) override;
	private:
		SurfaceVk& _Surface;
		const LogicalDeviceVk& _LogicalDevice;
		VkSwapchainKHR _NativeSwapchainHandle;
		
		Elysium::Core::uint32_t _CurrentBackBufferImageIndex;

		Elysium::Core::Collections::Template::Array<VkImage> _BackBufferImages;
		Elysium::Core::Collections::Template::Array<VkImageView> _BackBufferImageViews;

		void RecreateSwapchain(VkSwapchainKHR PreviousNativeSwapchainHandle);

		void Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk& Sender);
	};
}
#endif
