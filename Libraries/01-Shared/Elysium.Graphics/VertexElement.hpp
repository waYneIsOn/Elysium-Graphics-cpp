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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENTFORMAT
#include "VertexElementFormat.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENTUSAGE
#include "VertexElementUsage.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	/// <summary>
	/// Defines input vertex data to the pipeline.
	/// </summary>
	class ELYSIUM_GRAPHICS_API VertexElement final
	{
		friend class Elysium::Core::Template::Container::Vector<VertexElement>;
	private:
		VertexElement();
	public:
		VertexElement(const Elysium::Core::uint32_t Offset, const VertexElementFormat Format, const VertexElementUsage Usage, 
			const Elysium::Core::uint32_t UsageIndex);

		VertexElement(const VertexElement& Source);

		VertexElement(VertexElement&& Right) noexcept;

		~VertexElement();
	public:
		VertexElement& operator=(const VertexElement& Source);
		VertexElement& operator=(VertexElement&& Right) noexcept;
	public:
		const Elysium::Core::uint32_t GetOffset() const;

		const VertexElementFormat GetFormat() const;

		const VertexElementUsage GetUsage() const;

		const Elysium::Core::uint32_t GetUsageIndex() const;
	public:
		void SetOffset(const Elysium::Core::uint32_t Value);

		void SetFormat(const VertexElementFormat Value);

		void SetUsage(const VertexElementUsage Value);

		void SetUsageIndex(const Elysium::Core::uint32_t Value);
	private:
		Elysium::Core::uint32_t _Offset;
		VertexElementFormat _Format;
		VertexElementUsage _Usage;
		Elysium::Core::uint32_t _UsageIndex;
	};
}
#endif
