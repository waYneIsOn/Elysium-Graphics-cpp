/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSPIPELINEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSPIPELINEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSPIPELINE
#include "../Elysium.Graphics/INativeGraphicsPipeline.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API GraphicsPipelineVk final : public INativeGraphicsPipeline
	{
		friend class CommandBufferVk;
	public:
		GraphicsPipelineVk(const GraphicsDeviceVk& GraphicsDevice);
		GraphicsPipelineVk(const GraphicsPipelineVk& Source) = delete;
		GraphicsPipelineVk(GraphicsPipelineVk&& Right) noexcept = delete;
		virtual ~GraphicsPipelineVk();

		GraphicsPipelineVk& operator=(const GraphicsPipelineVk& Source) = delete;
		GraphicsPipelineVk& operator=(GraphicsPipelineVk&& Right) noexcept = delete;

		virtual void AddShaderModule(const INativeShaderModule& ShaderModule) override;
		virtual void Build() override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		VkPipeline _NativePipelineHandle;
		VkPipelineLayout _NativePipelineLayoutHandle;


	};
}
#endif