/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUECAPABILITIESVK
#include "QueueCapabilitiesVk.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API DeviceQueueCreateInfoVk final
	{
	public:
		DeviceQueueCreateInfoVk();
		DeviceQueueCreateInfoVk(const DeviceQueueCreateInfoVk& Source);
		DeviceQueueCreateInfoVk(DeviceQueueCreateInfoVk&& Right) noexcept;
		~DeviceQueueCreateInfoVk();

		DeviceQueueCreateInfoVk& operator=(const DeviceQueueCreateInfoVk& Source);
		DeviceQueueCreateInfoVk& operator=(DeviceQueueCreateInfoVk&& Right) noexcept;

		const Elysium::Core::uint32_t& GetFamilyIndex() const;
		const QueueCapabilitiesVk& GetCapabilities() const;
		const Elysium::Core::Template::Container::Vector<float>& GetPriorities() const;

		const void SetFamilyIndex(const Elysium::Core::uint32_t Value);
		const void SetCapabilities(const QueueCapabilitiesVk Value);

		const void AddPriority(const float Value);
		const void ClearPriorities();
	private:
		Elysium::Core::Template::Container::Vector<float> _Priorities;
		Elysium::Core::uint32_t _FamilyIndex;
		QueueCapabilitiesVk _Capabilities;
	};
}
#endif
