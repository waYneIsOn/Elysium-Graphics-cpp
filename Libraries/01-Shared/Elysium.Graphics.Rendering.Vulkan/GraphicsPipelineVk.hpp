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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#include "../Elysium.Graphics.Presentation/Control.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSPIPELINE
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
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API GraphicsPipelineVk final : public Native::INativeGraphicsPipeline
	{
		friend class CommandBufferVk;
	public:
		GraphicsPipelineVk(const GraphicsDeviceVk& GraphicsDevice);
		GraphicsPipelineVk(const GraphicsPipelineVk& Source) = delete;
		GraphicsPipelineVk(GraphicsPipelineVk&& Right) noexcept = delete;
		virtual ~GraphicsPipelineVk();

		GraphicsPipelineVk& operator=(const GraphicsPipelineVk& Source) = delete;
		GraphicsPipelineVk& operator=(GraphicsPipelineVk&& Right) noexcept = delete;

		virtual void AddShaderModule(const Native::INativeShaderModule& ShaderModule, const ShaderModuleType Type) override;
		virtual void Build(const Native::INativeRenderPass& RenderPass) override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		VkPipelineLayout _NativePipelineLayoutHandle;
		
		Elysium::Core::Collections::Template::List<VkPipelineShaderStageCreateInfo> _ShaderStages;
		VkPipelineVertexInputStateCreateInfo _VertexInputState;
		VkPipelineInputAssemblyStateCreateInfo _InputAssembly;
		VkViewport _Viewport;
		VkRect2D _ScissorRectangle;
		VkPipelineRasterizationStateCreateInfo _Rasterizer;
		VkPipelineMultisampleStateCreateInfo _Multisampling;
		VkPipelineColorBlendAttachmentState _ColorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo _ColorBlend;

		VkPipeline _NativePipelineHandle;

		VkPipelineLayout CreatePipelineLayout();
		VkPipelineVertexInputStateCreateInfo CreateDefaultVertexInputStateCreateInfo();
		VkPipelineInputAssemblyStateCreateInfo CreateDefaultInputAssemblyStateCreateInfo();
		VkViewport CreateDefaultViewport();
		VkRect2D CreateDefaultScissorRectangle();
		VkPipelineRasterizationStateCreateInfo CreateDefaultRasterizationStateCreateInfo();
		VkPipelineMultisampleStateCreateInfo CreateDefaultMultisampleStateCreateInfo();
		VkPipelineColorBlendAttachmentState CreateDefaultColorBlendAttachment();
		VkPipelineColorBlendStateCreateInfo CreateDefaultColorBlendStateCreateInfo();

		void DestroyNativePipeline();
		void DestroyNativePipelineLayout();

		void Control_SizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height);
	};
}
#endif