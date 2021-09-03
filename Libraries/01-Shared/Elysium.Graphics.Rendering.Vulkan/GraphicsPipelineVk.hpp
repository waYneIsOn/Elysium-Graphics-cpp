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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FRAMEBUFFERVK
#include "FrameBufferVk.hpp"
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

		virtual RasterizerState& GetRasterizerState() override;

		virtual void AddViewport(const Elysium::Core::uint32_t X, const Elysium::Core::uint32_t Y, const Elysium::Core::uint32_t Width,
			const Elysium::Core::uint32_t Height, const float MinimumDepth, const float MaximumDepth) override;
		virtual void ClearViewports() override;

		virtual void AddScissorRectangle(const Elysium::Core::int32_t X, const Elysium::Core::int32_t Y, const Elysium::Core::uint32_t Width,
			const Elysium::Core::uint32_t Height) override;
		virtual void ClearScissorRectangles() override;

		virtual void AddShaderModule(const Native::INativeShaderModule& ShaderModule, const ShaderModuleType Type) override;
		virtual void ClearShaderModules() override;

		virtual void SetVertexBuffer(const Native::INativeVertexBuffer& VertexBuffer, const Elysium::Core::uint32_t VertexOffset) override;

		virtual void Build(const Native::INativeRenderPass& RenderPass) override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		RasterizerState _RasterizerState;

		VkPipelineLayout _NativePipelineLayoutHandle;
		VkPipeline _NativePipelineHandle;

		Elysium::Core::Collections::Template::List<VkViewport> _Viewports;
		Elysium::Core::Collections::Template::List<VkRect2D> _ScissorRectangles;
		Elysium::Core::Collections::Template::List<VkPipelineShaderStageCreateInfo> _ShaderStages;

		Elysium::Core::Collections::Template::List<VkVertexInputBindingDescription> _InputBindingDescriptions;
		Elysium::Core::Collections::Template::List<VkVertexInputAttributeDescription> _InputAttributeDescriptions;
		VkPipelineVertexInputStateCreateInfo _PipelineVertexInputStateCreateInfo;

		VkPipelineInputAssemblyStateCreateInfo _InputAssembly;
		VkPipelineMultisampleStateCreateInfo _Multisampling;
		VkPipelineColorBlendAttachmentState _ColorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo _ColorBlend;

		VkPipelineLayout CreatePipelineLayout();

		VkPipelineVertexInputStateCreateInfo CreateDefaultVertexInputStateCreateInfo();
		VkPipelineInputAssemblyStateCreateInfo CreateDefaultInputAssemblyStateCreateInfo();
		VkPipelineMultisampleStateCreateInfo CreateDefaultMultisampleStateCreateInfo();
		VkPipelineColorBlendAttachmentState CreateDefaultColorBlendAttachment();
		VkPipelineColorBlendStateCreateInfo CreateDefaultColorBlendStateCreateInfo();

		void DestroyNativePipeline();
		void DestroyNativePipelineLayout();
	};
}
#endif