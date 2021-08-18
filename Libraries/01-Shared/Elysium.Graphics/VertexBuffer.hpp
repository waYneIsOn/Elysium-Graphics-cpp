/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_VERTEXBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXDECLARATION
#include "VertexDeclaration.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEVERTEXBUFFER
#include "INativeVertexBuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;

	/// <summary>
	/// Represents a list of 3D vertices to be streamed to the graphics device.
	/// </summary>
	class ELYSIUM_GRAPHICS_API VertexBuffer final
	{
	public:
		VertexBuffer(const GraphicsDevice& GraphicsDevice, const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount, const BufferUsage Usage);
		VertexBuffer(const VertexBuffer& Source) = delete;
		VertexBuffer(VertexBuffer&& Right) noexcept = delete;
		~VertexBuffer();

		VertexBuffer& operator=(const VertexBuffer& Source) = delete;
		VertexBuffer& operator=(VertexBuffer&& Right) noexcept = delete;

		const BufferUsage GetBufferUsage() const;
		const Elysium::Core::uint32_t GetVertexCount() const;
		const VertexDeclaration& GetVertexDeclaration() const;
		/*
		template <class T>
		void SetData();
		*/
	private:
		const GraphicsDevice& _GraphicsDevice;

		Native::INativeVertexBuffer* _NativeVertexBuffer;
	};
}
#endif
