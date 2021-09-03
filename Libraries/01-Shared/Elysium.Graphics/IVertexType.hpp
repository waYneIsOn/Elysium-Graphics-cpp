/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_IVERTEXTYPE
#define ELYSIUM_GRAPHICS_RENDERING_IVERTEXTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXDECLARATION
#include "VertexDeclaration.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API IVertexType
	{
	public:
		virtual ~IVertexType() { }

		virtual const VertexDeclaration& GetVertexDeclaration() const = 0;
	};
}
#endif
