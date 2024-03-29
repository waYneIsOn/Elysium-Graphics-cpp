/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDPOOLVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDPOOLVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDPOOL
#include "../Elysium.Graphics/INativeCommandPool.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDBUFFERVK
#include "CommandBufferVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEVK
#include "QueueVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class CommandBufferVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API CommandPoolVk final : public Native::INativeCommandPool
	{
		friend class CommandBufferVk;
	public:
		CommandPoolVk(const GraphicsDeviceVk& GraphicsDevice, const QueueVk& Queue);
		CommandPoolVk(const CommandPoolVk& Source) = delete;
		CommandPoolVk(CommandPoolVk&& Right) noexcept = delete;
		virtual ~CommandPoolVk();

		CommandPoolVk& operator=(const CommandPoolVk& Source) = delete;
		CommandPoolVk& operator=(CommandPoolVk&& Right) noexcept = delete;

		virtual Native::INativeCommandBuffer* CreateCommandBuffer(const bool IsPrimary) override;

		virtual void Reset() override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		const QueueVk& _Queue;
		VkCommandPool _NativeCommandPoolHandle;

		VkCommandPool CreateNativeCommandPool();

		void DestroyNativeCommandPool();
	};
}
#endif
