/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXPOSITIONCOLOR
#define ELYSIUM_GRAPHICS_RENDERING_VERTEXPOSITIONCOLOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3SINGLE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Math/Vector3Single.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_COLOR
#include "Color.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXDECLARATION
#include "VertexDeclaration.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API VertexPositionColor final
	{
		friend class Elysium::Core::Template::Container::Vector<VertexPositionColor>;
	private:
		VertexPositionColor();
	public:
		VertexPositionColor(const Elysium::Core::Math::Numerics::Vector3<float>& Position, const Color Color);

		VertexPositionColor(const VertexPositionColor& Source);

		VertexPositionColor(VertexPositionColor&& Right) noexcept = delete;

		~VertexPositionColor();
	public:
		VertexPositionColor& operator=(const VertexPositionColor& Source);

		VertexPositionColor& operator=(VertexPositionColor&& Right) noexcept = delete;
	public:
		Elysium::Core::Math::Numerics::Vector3<float> Position;
		Color Color;
	public:
		const VertexDeclaration& GetVertexDeclaration() const;
	private:
		static const VertexDeclaration _Declaration;

		static const VertexDeclaration CreateVertexDeclaration();
	};
}
#endif
