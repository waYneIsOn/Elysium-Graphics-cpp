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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "../Elysium.Graphics/INativePhysicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENSIONPROPERTYVK
#include "ExtensionPropertyVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class DepthBufferVk;
	class GraphicsInstanceVk;
	class LogicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API PhysicalDeviceVk final : public INativePhysicalDevice
	{
		friend class Elysium::Core::Collections::Template::Array<PhysicalDeviceVk>;
		friend class DepthBufferVk;
		friend class GraphicsInstanceVk;
		friend class LogicalDeviceVk;
		friend class SurfaceVk;
	public:
		PhysicalDeviceVk(const PhysicalDeviceVk& Source) = delete;
		PhysicalDeviceVk(PhysicalDeviceVk&& Right) noexcept = delete;
		virtual ~PhysicalDeviceVk();

		PhysicalDeviceVk& operator=(const PhysicalDeviceVk& Source) = delete;
		PhysicalDeviceVk& operator=(PhysicalDeviceVk&& Right) noexcept = delete;

		virtual const Elysium::Core::String GetName() const override;
		virtual const PhysicalDeviceType GetDeviceType() const override;

		const PhysicalDevicePropertiesVk& GetProperties() const;
		const PhysicalDeviceFeaturesVk& GetFeatures() const;
		const Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk> GetQueueFamilyProperties() const;
		const Elysium::Core::Collections::Template::Array<ExtensionPropertyVk> GetAvailableExtensions() const;

		const bool SupportsPresentation(const SurfaceVk& Surface, const Elysium::Core::uint32_t FamilyIndex) const;
	private:
		PhysicalDeviceVk();

		VkPhysicalDevice _NativePhysicalDeviceHandle;
		PhysicalDevicePropertiesVk _Properties;
		PhysicalDeviceFeaturesVk _Features;
	};
}
#endif
