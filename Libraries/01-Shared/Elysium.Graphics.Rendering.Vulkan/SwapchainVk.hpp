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

#ifndef ELYSIUM_GRAPHICS_RENDERING_ISWAPCHAIN
#include "../Elysium.Graphics/ISwapchain.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class LogicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SwapchainVk final : public ISwapchain
	{
		friend class LogicalDeviceVk;
	public:
		SwapchainVk(const SwapchainVk& Source) = delete;
		SwapchainVk(SwapchainVk&& Right) noexcept = delete;
		virtual ~SwapchainVk();

		SwapchainVk& operator=(const SwapchainVk& Source) = delete;
		SwapchainVk& operator=(SwapchainVk&& Right) noexcept = delete;
	private:
		SwapchainVk(const VkDevice NativeLogicalDeviceHandle, const VkSwapchainKHR NativeSwapchainHandle, const Elysium::Core::Collections::Template::Array<VkImage>& BackBufferImages, const Elysium::Core::Collections::Template::Array<VkImageView> BackBufferImageViews);

		const VkDevice _NativeLogicalDeviceHandle;
		const VkSwapchainKHR _NativeSwapchainHandle;
		const Elysium::Core::Collections::Template::Array<VkImage> _BackBufferImages;
		const Elysium::Core::Collections::Template::Array<VkImageView> _BackBufferImageViews;
	};
}
#endif
