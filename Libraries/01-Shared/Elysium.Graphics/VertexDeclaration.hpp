/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXDECLARATION
#define ELYSIUM_GRAPHICS_RENDERING_VERTEXDECLARATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENT
#include "VertexElement.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	/// <summary>
	/// A vertex declaration, which defines per-vertex data.
	/// </summary>
	class ELYSIUM_GRAPHICS_API VertexDeclaration final
	{
	public:
		VertexDeclaration(const Elysium::Core::uint32_t Stride);
		VertexDeclaration(const VertexDeclaration& Source) = delete;
		VertexDeclaration(VertexDeclaration&& Right) noexcept = delete;
		~VertexDeclaration();

		VertexDeclaration& operator=(const VertexDeclaration& Source) = delete;
		VertexDeclaration& operator=(VertexDeclaration&& Right) noexcept = delete;

		/// <summary>
		/// Gets the number of bytes from one vertex to the next.
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::uint32_t GetVertexStride() const;
	private:
		const Elysium::Core::uint32_t _Stride;
	};
}
#endif
