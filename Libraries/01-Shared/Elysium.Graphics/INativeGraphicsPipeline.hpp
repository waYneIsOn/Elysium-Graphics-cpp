/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSPIPELINE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSPIPELINE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPIPELINE
#include "INativePipeline.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESHADERMODULE
#include "INativeShaderModule.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeGraphicsPipeline : public INativePipeline
	{
	public:
		virtual ~INativeGraphicsPipeline() { }

		virtual void AddShaderModule(const INativeShaderModule& ShaderModule) = 0;
		//virtual void AddViewport() = 0;
		//virtual void AddScissorRectangle() = 0;
	};
}
#endif
