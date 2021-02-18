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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEQUEUE
#include "../Elysium.Graphics/INativeQueue.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class Array;
}

namespace Elysium::Graphics::Rendering::Vulkan
{
	class PhysicalDeviceVk;
	class SwapchainVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API QueueVk final : public INativeQueue
	{
		friend class Elysium::Core::Collections::Template::Array<QueueVk>;
		friend class PhysicalDeviceVk;
		friend class SwapchainVk;
	public:
		QueueVk(const LogicalDeviceVk& LogicalDevice, const Elysium::Core::uint32_t FamilyIndex, Elysium::Core::uint32_t Index);
		QueueVk(const QueueVk& Source) = delete;
		QueueVk(QueueVk&& Right) noexcept = delete;
		virtual ~QueueVk();

		QueueVk& operator=(const QueueVk& Source) = delete;
		QueueVk& operator=(QueueVk&& Right) noexcept = delete;

		virtual const Elysium::Core::uint32_t GetFamilyIndex() const override;

		virtual void Submit(const INativeSemaphore& PresentSemaphore, const INativeSemaphore& RenderSemaphore, const INativeFence& Fence) override;
		virtual void Wait() const override;
	private:
		const LogicalDeviceVk& _LogicalDevice;
		const Elysium::Core::uint32_t _FamilyIndex;
		const Elysium::Core::uint32_t _Index;
		VkQueue _NativeQueueHandle;
	};
}
#endif
