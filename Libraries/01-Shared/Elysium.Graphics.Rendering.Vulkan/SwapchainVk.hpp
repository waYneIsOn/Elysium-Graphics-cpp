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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_GAME
#include "../Elysium.Graphics/Game.hpp"
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

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SwapchainVk final : public INativeSwapchain
	{
	public:
		SwapchainVk(const LogicalDeviceVk& LogicalDevice);
		SwapchainVk(const SwapchainVk& Source) = delete;
		SwapchainVk(SwapchainVk&& Right) noexcept = delete;
		virtual ~SwapchainVk();

		SwapchainVk& operator=(const SwapchainVk& Source) = delete;
		SwapchainVk& operator=(SwapchainVk&& Right) noexcept = delete;

		virtual const Elysium::Core::uint32_t GetBackBufferImageCount() const override;

		virtual void Recreate() override;
		virtual void AquireNextImage(const Elysium::Core::uint64_t Timeout) override;
		virtual void PresentFrame(const INativeQueue& PresentationQueue) override;
	private:
		const LogicalDeviceVk& _LogicalDevice;
		VkSwapchainKHR _NativeSwapchainHandle;

		Elysium::Core::uint32_t _CurrentBackBufferImageIndex;

		Elysium::Core::Collections::Template::Array<VkImage> _BackBufferImages;
		Elysium::Core::Collections::Template::Array<VkImageView> _BackBufferImageViews;

		Elysium::Core::Collections::Template::Array<VkFence> _Fences;
		Elysium::Core::Collections::Template::Array<VkSemaphore> _ImageAvailableSemaphores;
		Elysium::Core::Collections::Template::Array<VkSemaphore> _RendererFinishedSemaphores;

		void RecreateSwapchain(VkSwapchainKHR PreviousNativeSwapchainHandle);
	};
}
#endif
