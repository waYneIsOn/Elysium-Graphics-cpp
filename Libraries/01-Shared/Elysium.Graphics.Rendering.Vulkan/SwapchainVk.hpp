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
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SwapchainVk final
	{
		friend class CommandBufferVk;
		friend class FramebufferVk;
	public:
		SwapchainVk(const LogicalDeviceVk& LogicalDevice, SurfaceVk& Surface);
		SwapchainVk(const SwapchainVk& Source) = delete;
		SwapchainVk(SwapchainVk&& Right) noexcept = delete;
		~SwapchainVk();

		SwapchainVk& operator=(const SwapchainVk& Source) = delete;
		SwapchainVk& operator=(SwapchainVk&& Right) noexcept = delete;

		const Elysium::Core::uint32_t GetBackBufferImageCount() const;

		void AquireNextImage(const INativeSemaphore& PresentSemaphore, const Elysium::Core::uint64_t Timeout);
		void PresentFrame(const INativeSemaphore& RenderSemaphore, const INativeQueue& PresentationQueue);
	private:
		const LogicalDeviceVk& _LogicalDevice;
		SurfaceVk& _Surface;
		VkSwapchainKHR _NativeSwapchainHandle;
		
		Elysium::Core::uint32_t _CurrentBackBufferImageIndex;

		Elysium::Core::Collections::Template::Array<VkImage> _BackBufferImages;
		Elysium::Core::Collections::Template::Array<VkImageView> _BackBufferImageViews;

		void RecreateSwapchain(VkSwapchainKHR PreviousNativeSwapchainHandle);
		
		void Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk& Sender);
	};
}
#endif
