/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEQUEUE
#include "../Elysium.Graphics/INativeQueue.hpp"
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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API QueueVk final : public Native::INativeQueue
	{
		friend class Elysium::Core::Collections::Template::Array<QueueVk>;
		friend class CommandPoolVk;
		friend class GraphicsDeviceVk;
		friend class PhysicalDeviceVk;
	public:
		QueueVk(const GraphicsDeviceVk& GraphicsDevice, const Elysium::Core::uint32_t FamilyIndex, Elysium::Core::uint32_t Index);
		QueueVk(const QueueVk& Source) = delete;
		QueueVk(QueueVk&& Right) noexcept = delete;
		virtual ~QueueVk();

		QueueVk& operator=(const QueueVk& Source) = delete;
		QueueVk& operator=(QueueVk&& Right) noexcept = delete;

		virtual const Elysium::Core::uint32_t GetFamilyIndex() const override;

		virtual Native::INativeCommandPool* CreateCommandPool() override;

		virtual void Submit(const Native::INativeCommandBuffer& CommmandBuffer, const Native::INativeSemaphore& PresentSemaphore, const Native::INativeSemaphore& RenderSemaphore, const Native::INativeFence& Fence) override;
		virtual void Wait() const override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		const Elysium::Core::uint32_t _FamilyIndex;
		const Elysium::Core::uint32_t _Index;
		const VkQueue _NativeQueueHandle;

		const VkQueue RetrieveNativeQueue();
	};
}
#endif
