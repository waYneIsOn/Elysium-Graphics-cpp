/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INDEXBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_INDEXBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_BUFFERUSAGE
#include "BufferUsage.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INDEXELEMENTSIZE
#include "IndexElementSize.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEINDEXBUFFER
#include "INativeIndexBuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;

	class ELYSIUM_GRAPHICS_API IndexBuffer final
	{
		friend class CommandBuffer;
		friend class GraphicsPipeline;
	public:
		IndexBuffer(const GraphicsDevice& GraphicsDevice, const IndexElementSize ElementSize, const Elysium::Core::uint32_t IndexCount,
			const BufferUsage Usage);
		IndexBuffer(const IndexBuffer& Source) = delete;
		IndexBuffer(IndexBuffer&& Right) noexcept = delete;
		~IndexBuffer();

		IndexBuffer& operator=(const IndexBuffer& Source) = delete;
		IndexBuffer& operator=(IndexBuffer&& Right) noexcept = delete;

		const BufferUsage GetBufferUsage() const;
		const Elysium::Core::uint32_t GetIndexCount() const;
		const IndexElementSize GetIndexElementSize() const;

		void SetData(const void* First, const size_t Length);
	private:
		const GraphicsDevice& _GraphicsDevice;

		Native::INativeIndexBuffer* _NativeIndexBuffer;
	};
}
#endif
