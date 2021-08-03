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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVECOMMANDBUFFER
#include "../Elysium.Graphics/INativeCommandBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDPOOLVK
#include "CommandPoolVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class QueueVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API CommandBufferVk : public INativeCommandBuffer
	{
		friend class QueueVk;
	public:
		CommandBufferVk(const GraphicsDeviceVk& GraphicsDevice, const LogicalDeviceVk& LogicalDevice, const CommandPoolVk& CommandPool, const bool IsPrimary);
		CommandBufferVk(const CommandBufferVk& Source) = delete;
		CommandBufferVk(CommandBufferVk&& Right) noexcept = delete;
		virtual ~CommandBufferVk();

		CommandBufferVk& operator=(const CommandBufferVk& Source) = delete;
		CommandBufferVk& operator=(CommandBufferVk&& Right) noexcept = delete;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Reset() override;

		virtual void BeginRenderPass(const INativeRenderPass& RenderPass, const INativeFramebuffer& FrameBuffer) override;
		virtual void EndRenderPass() override;

		virtual void ClearBackBufferImage(const Color& ClearColor) override;
		virtual void ClearDepthImage(const float Depth, const Elysium::Core::int32_t Stencil) override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		const LogicalDeviceVk& _LogicalDevice;
		const CommandPoolVk& _CommandPool;
		const bool _IsPrimary;
		const Elysium::Core::Collections::Template::Array<VkCommandBuffer> _NativeCommandBufferHandles;

		Elysium::Core::Collections::Template::Array<VkCommandBuffer> CreateNativeCommandBuffers();
		void DestroyNativeCommandBuffers();
	};
}
#endif
