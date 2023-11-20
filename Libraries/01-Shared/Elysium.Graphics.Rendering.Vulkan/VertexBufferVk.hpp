/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_VERTEXBUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_VERTEXBUFFERVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEVERTEXBUFFER
#include "../Elysium.Graphics/INativeVertexBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API VertexBufferVk final : public Native::INativeVertexBuffer
	{
		friend class CommandBufferVk;
	public:
		VertexBufferVk(const GraphicsDeviceVk& GraphicsDevice, const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount,
			const BufferUsage Usage);

		VertexBufferVk(const VertexBufferVk& Source) = delete;

		VertexBufferVk(VertexBufferVk&& Right) noexcept = delete;

		virtual ~VertexBufferVk();
	public:
		VertexBufferVk& operator=(const VertexBufferVk& Source) = delete;

		VertexBufferVk& operator=(VertexBufferVk&& Right) noexcept = delete;
	public:
		virtual const BufferUsage GetBufferUsage() const override;

		virtual const Elysium::Core::uint32_t GetVertexCount() const override;

		virtual const VertexDeclaration& GetVertexDeclaration() const override;
	public:
		virtual void SetData(const void* First, const size_t Length) override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		const VertexDeclaration& _Declaration;
		const Elysium::Core::uint32_t _VertexCount;
		const BufferUsage _Usage;

		VkBuffer _NativeVertexBuffer;
		VkDeviceMemory _NativeVertexBufferMemory;
	public:
		VkBuffer CreateNativeVertexBuffer();

		VkDeviceMemory CreateNativeVertexBufferMemory();

		void DestroyNativeVertexBufferMemory();

		void DestroyNativeVertexBuffer();
	};
}
#endif
