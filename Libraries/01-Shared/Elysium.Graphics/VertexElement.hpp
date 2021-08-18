/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENT
#define ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	/// <summary>
	/// Defines input vertex data to the pipeline.
	/// </summary>
	class ELYSIUM_GRAPHICS_API VertexElement final
	{
	public:
		//VertexElement(const Elysium::Core::uint32_t Stride);
		VertexElement(const VertexElement& Source) = delete;
		VertexElement(VertexElement&& Right) noexcept = delete;
		~VertexElement();

		VertexElement& operator=(const VertexElement& Source) = delete;
		VertexElement& operator=(VertexElement&& Right) noexcept = delete;
	};
}
#endif
