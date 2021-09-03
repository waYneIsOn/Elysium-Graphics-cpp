/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEVERTEXBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEVERTEXBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_BUFFERUSAGE
#include "BufferUsage.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_IVERTEXTYPE
#include "IVertexType.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXDECLARATION
#include "VertexDeclaration.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeVertexBuffer
	{
	public:
		virtual ~INativeVertexBuffer() { }

		virtual const BufferUsage GetBufferUsage() const = 0;
		virtual const Elysium::Core::uint32_t GetVertexCount() const = 0;
		virtual const VertexDeclaration& GetVertexDeclaration() const = 0;
		
		virtual void SetData(const IVertexType* First, const size_t Length) = 0;
	};
}
#endif
