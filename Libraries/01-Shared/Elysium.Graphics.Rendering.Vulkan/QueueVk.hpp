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

#ifndef ELYSIUM_GRAPHICS_RENDERING_IQUEUE
#include "../Elysium.Graphics/IQueue.hpp"
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

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class Array;
}

namespace Elysium::Graphics::Rendering::Vulkan
{
	class LogicalDeviceVk;
	class PhysicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API QueueVk final : public IQueue
	{
		friend class Elysium::Core::Collections::Template::Array<QueueVk>;
		friend class LogicalDeviceVk;
		friend class PhysicalDeviceVk;
	public:
		QueueVk(const QueueVk& Source) = delete;
		QueueVk(QueueVk&& Right) noexcept = delete;
		virtual ~QueueVk();

		QueueVk& operator=(const QueueVk& Source) = delete;
		QueueVk& operator=(QueueVk&& Right) noexcept = delete;
	private:
		QueueVk();

		VkQueue _NativeQueueHandle;
		Elysium::Core::uint32_t _FamilyIndex;
		Elysium::Core::uint32_t _Index;
	};
}
#endif
