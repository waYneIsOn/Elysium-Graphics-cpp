/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDBUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDBUFFERVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDBUFFER
#include "../Elysium.Graphics/INativeCommandBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class CommandPoolVk;
	class GraphicsDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API CommandBufferVk : public Native::INativeCommandBuffer
	{
		friend class QueueVk;
	public:
		CommandBufferVk(const GraphicsDeviceVk& GraphicsDevice, const CommandPoolVk& CommandPool, const bool IsPrimary);
		CommandBufferVk(const CommandBufferVk& Source) = delete;
		CommandBufferVk(CommandBufferVk&& Right) noexcept = delete;
		virtual ~CommandBufferVk();

		CommandBufferVk& operator=(const CommandBufferVk& Source) = delete;
		CommandBufferVk& operator=(CommandBufferVk&& Right) noexcept = delete;

		virtual void BeginRecording() override;
		virtual void EndRecording() override;
		virtual void Reset() override;

		virtual void RecordSecondaryBuffer(const INativeCommandBuffer& CommandBuffer) override;

		virtual void RecordBeginRenderPass(const Native::INativeRenderPass& RenderPass, const Native::INativeFrameBuffer& FrameBuffer,
			const Color& ClearColor, const float Depth, const Elysium::Core::uint32_t Stencil) override;
		virtual void RecordEndRenderPass() override;

		virtual void RecordSetGraphicsPipeline(const Native::INativeGraphicsPipeline& GraphicsPipeline) override;

		virtual void RecordSetVertexBuffer(const Native::INativeVertexBuffer& VertexBuffer) override;

		virtual void RecordSetIndexBuffer(const Native::INativeIndexBuffer& IndexBuffer) override;

		virtual void RecordDrawPrimitives(const Elysium::Core::uint32_t VertexCount, const Elysium::Core::uint32_t InstanceCount, 
			const Elysium::Core::uint32_t FirstVertex, const Elysium::Core::uint32_t FirstInstance) override;

		virtual void RecordDrawIndexedPrimitives(const PrimitiveType PrimitiveType, const Elysium::Core::uint32_t BaseVertex,
			const Elysium::Core::uint32_t MinimumVertexIndex, const Elysium::Core::uint32_t NumberVertices, const Elysium::Core::uint32_t StartIndex,
			const Elysium::Core::uint32_t NumberIndices) override;
		
		virtual void RecordBlit(const Native::INativeFrameBuffer& FrameBuffer, const BlitFilter Filter) override;

		virtual void RecordClearBackBufferColorImage(const Color& ClearColor) override;
		virtual void RecordClearBackBufferDepthImage(const float Depth, const Elysium::Core::uint32_t Stencil) override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		const CommandPoolVk& _CommandPool;
		const bool _IsPrimary;
		const Elysium::Core::Collections::Template::Array<VkCommandBuffer> _NativeCommandBufferHandles;

		Elysium::Core::Collections::Template::Array<VkCommandBuffer> CreateNativeCommandBuffers();

		void RecordInsertImageMemoryBarrier(const VkCommandBuffer CommandBuffer, const VkImage Image, 
			const VkAccessFlags SourceAccessMask, const VkImageLayout OldLayout, const VkPipelineStageFlags SourceStageFlags,
			const VkAccessFlags TargetAccessMask, const VkImageLayout NewLayout, const VkPipelineStageFlags TargetStageFlags,
			const VkImageSubresourceRange ImageSubresourceRange);

		void DestroyNativeCommandBuffers();
	};
}
#endif
