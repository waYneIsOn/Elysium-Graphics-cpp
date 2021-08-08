/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSPIPELINE
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSPIPELINE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVERENDERPASS
#include "INativeRenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESHADERMODULE
#include "INativeShaderModule.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SHADERMODULETYPE
#include "ShaderModuleType.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeGraphicsPipeline
	{
	public:
		virtual ~INativeGraphicsPipeline() { }

		virtual void AddShaderModule(const INativeShaderModule& ShaderModule, const ShaderModuleType Type) = 0;
		//virtual void AddViewport() = 0;
		//virtual void AddScissorRectangle() = 0;

		virtual void Build(const INativeRenderPass& RenderPass) = 0;
	};
}
#endif
