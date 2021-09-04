/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INDEXBUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_INDEXBUFFERVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEINDEXBUFFER
#include "../Elysium.Graphics/INativeIndexBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API IndexBufferVk final : public Native::INativeIndexBuffer
	{
		friend class CommandBufferVk;
	public:
		IndexBufferVk(const GraphicsDeviceVk & GraphicsDevice, const IndexElementSize ElementSize, const Elysium::Core::uint32_t IndexCount, 
			const BufferUsage Usage);
		IndexBufferVk(const IndexBufferVk& Source) = delete;
		IndexBufferVk(IndexBufferVk&& Right) noexcept = delete;
		virtual ~IndexBufferVk();

		IndexBufferVk& operator=(const IndexBufferVk& Source) = delete;
		IndexBufferVk& operator=(IndexBufferVk&& Right) noexcept = delete;

		virtual const BufferUsage GetBufferUsage() const override;
		virtual const Elysium::Core::uint32_t GetIndexCount() const override;
		virtual const IndexElementSize GetIndexElementSize() const override;

		virtual void SetData(const void* First, const size_t Length) override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		const IndexElementSize _ElementSize;
		const Elysium::Core::uint32_t _IndexCount;
		const BufferUsage _Usage;

		VkBuffer _NativeIndexBuffer;
		VkDeviceMemory _NativeIndexBufferMemory;

		VkBuffer CreateNativeIndexBuffer();
		VkDeviceMemory CreateNativeIndexBufferMemory();

		void DestroyNativeIndexBufferMemory();
		void DestroyNativeIndexBuffer();
	};
}
#endif
