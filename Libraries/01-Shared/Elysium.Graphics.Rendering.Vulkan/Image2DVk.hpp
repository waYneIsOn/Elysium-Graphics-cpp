/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
/*
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_IMAGE2DVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_IMAGE2DVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEIMAGE2D
#include "../Elysium.Graphics/INativeImage2D.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API Image2DVk final : public INativeImage2D
	{
	public:
		Image2DVk(const Image2DVk& Source) = delete;
		Image2DVk(Image2DVk&& Right) noexcept = delete;
		virtual ~Image2DVk();

		Image2DVk& operator=(const Image2DVk& Source) = delete;
		Image2DVk& operator=(Image2DVk&& Right) noexcept = delete;

		virtual const SurfaceFormat& GetFormat() const override;
		virtual const Elysium::Core::uint32_t& GetLevelCount() const override;

		virtual const Elysium::Core::uint32_t& GetWidth() const override;
		virtual const Elysium::Core::uint32_t& GetHeight() const override;
	private:
		Image2DVk(const VkDevice NativeLogicalDeviceHandle, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height, const bool MipMap, const SurfaceFormat& Format);

		const VkDevice _NativeLogicalDeviceHandle;

		const VkImage _NativeDepthImageHandle = VK_NULL_HANDLE;
		const VkDeviceMemory _NativeDepthImageMemoryHandle = VK_NULL_HANDLE;
		const VkImageView _NativeDepthImageViewHandle = VK_NULL_HANDLE;
	};
}
#endif
*/