/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_SHADERMODULETYPE
#define ELYSIUM_GRAPHICS_RENDERING_SHADERMODULETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/System.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class ShaderModuleType : Elysium::Core::uint16_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class ShaderModuleType
#else
#error "undefined os"
#endif
	{
		VertexShader = 1,

		FragmentShader = 16,
	};
}
#endif
