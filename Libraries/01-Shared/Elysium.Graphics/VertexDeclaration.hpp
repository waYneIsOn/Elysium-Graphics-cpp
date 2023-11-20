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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
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
		VertexDeclaration(Elysium::Core::Template::Container::Vector<VertexElement>&& Elements);

		VertexDeclaration(const Elysium::Core::uint32_t Stride, Elysium::Core::Template::Container::Vector<VertexElement>&& Elements);

		VertexDeclaration(const VertexDeclaration& Source) = delete;

		VertexDeclaration(VertexDeclaration&& Right) noexcept = delete;

		~VertexDeclaration();
	public:
		VertexDeclaration& operator=(const VertexDeclaration& Source) = delete;

		VertexDeclaration& operator=(VertexDeclaration&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Gets the number of bytes from one vertex to the next.
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::uint32_t GetVertexStride() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::Template::Container::Vector<VertexElement>& GetElements() const;
	private:
		static const Elysium::Core::uint32_t GetElementStride(const Elysium::Core::Template::Container::Vector<VertexElement>& Elements);
		static const Elysium::Core::uint32_t GetElementStride(const VertexElementFormat Format);
	private:
		const Elysium::Core::uint32_t _Stride;
		const Elysium::Core::Template::Container::Vector<VertexElement> _Elements;
	};
}
#endif
