/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_IPHYSICALDEVICE
#include "../Elysium.Graphics/IPhysicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK
#include "DeviceQueueCreateInfoVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEFEATURESVK
#include "PhysicalDeviceFeaturesVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEPROPERTIESVK
#include "PhysicalDevicePropertiesVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#include "PresentationParametersVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEFAMILYPROPERTYVK
#include "QueueFamilyPropertyVk.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class Array;
}

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsInstanceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API PhysicalDeviceVk final : public IPhysicalDevice
	{
		friend class Elysium::Core::Collections::Template::Array<PhysicalDeviceVk>;
		friend class GraphicsInstanceVk;
	public:
		PhysicalDeviceVk(const PhysicalDeviceVk& Source) = delete;
		PhysicalDeviceVk(PhysicalDeviceVk&& Right) noexcept = delete;
		~PhysicalDeviceVk();

		PhysicalDeviceVk& operator=(const PhysicalDeviceVk& Source) = delete;
		PhysicalDeviceVk& operator=(PhysicalDeviceVk&& Right) noexcept = delete;

		virtual const Elysium::Core::String GetName() const override;
		const PhysicalDevicePropertiesVk& GetProperties() const;
		const PhysicalDeviceFeaturesVk& GetFeatures() const;

		const Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk> GetQueueFamilyProperties();

		LogicalDeviceVk CreateLogicalDevice(const PresentationParametersVk& PresentationParameters, const Elysium::Core::Collections::Template::List<DeviceQueueCreateInfoVk>& DeviceQueueCreateInfos);
	private:
		PhysicalDeviceVk();

		VkPhysicalDevice _NativePhysicalDeviceHandle;
		PhysicalDevicePropertiesVk _Properties;
		PhysicalDeviceFeaturesVk _Features;
	};
}
#endif
