/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEINDEXBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEINDEXBUFFER

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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INDEXELEMENTSIZE
#include "IndexElementSize.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeIndexBuffer
	{
	public:
		virtual ~INativeIndexBuffer() { }

		virtual const BufferUsage GetBufferUsage() const = 0;
		virtual const Elysium::Core::uint32_t GetIndexCount() const = 0;
		virtual const IndexElementSize GetIndexElementSize() const = 0;

		virtual void SetData(const void* First, const size_t Length) = 0;
	};
}
#endif
