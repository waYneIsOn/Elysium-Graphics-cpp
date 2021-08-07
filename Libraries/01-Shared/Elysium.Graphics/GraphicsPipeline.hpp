/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSPIPELINE
#define ELYSIUM_GRAPHICS_RENDERING_GRAPHICSPIPELINE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSPIPELINE
#include "INativeGraphicsPipeline.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_RENDERPASS
#include "RenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SHADERMODULE
#include "ShaderModule.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;

	class ELYSIUM_GRAPHICS_API GraphicsPipeline final
	{
		friend class CommandBuffer;
	public:
		GraphicsPipeline(const GraphicsDevice& GraphicsDevice);
		GraphicsPipeline(const GraphicsPipeline& Source) = delete;
		GraphicsPipeline(GraphicsPipeline&& Right) noexcept = delete;
		~GraphicsPipeline();

		GraphicsPipeline& operator=(const GraphicsPipeline& Source) = delete;
		GraphicsPipeline& operator=(GraphicsPipeline&& Right) noexcept = delete;

		void AddShaderModule(const ShaderModule& ShaderModule, const ShaderModuleType Type);
		void Build(const RenderPass& RenderPass);
	private:
		const GraphicsDevice& _GraphicsDevice;

		INativeGraphicsPipeline* _NativeGraphicsPipeline;
	};
}
#endif
