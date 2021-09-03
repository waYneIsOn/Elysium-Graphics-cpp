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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
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
		VertexDeclaration(Elysium::Core::Collections::Template::Array<VertexElement>&& Elements);
		VertexDeclaration(const Elysium::Core::uint32_t Stride, Elysium::Core::Collections::Template::Array<VertexElement>&& Elements);
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

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::Collections::Template::Array<VertexElement>& GetElements() const;
	private:
		const Elysium::Core::uint32_t _Stride;
		const Elysium::Core::Collections::Template::Array<VertexElement> _Elements;

		static const Elysium::Core::uint32_t GetElementStride(const Elysium::Core::Collections::Template::Array<VertexElement>& Elements);
		static const Elysium::Core::uint32_t GetElementStride(const VertexElementFormat Format);
	};
}
#endif
