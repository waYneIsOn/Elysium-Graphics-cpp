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

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEPHYSICALDEVICE
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

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API PhysicalDeviceVk final : public Native::INativePhysicalDevice
	{
		friend class Elysium::Core::Collections::Template::Array<PhysicalDeviceVk>;
		friend class DepthBufferVk;
		friend class FrameBufferVk;
		friend class GraphicsDeviceVk;
		friend class GraphicsInstanceVk;
		friend class IndexBufferVk;
		friend class VertexBufferVk;
	public:
		PhysicalDeviceVk(const PhysicalDeviceVk& Source) = delete;
		PhysicalDeviceVk(PhysicalDeviceVk&& Right) noexcept = delete;
		virtual ~PhysicalDeviceVk();

		PhysicalDeviceVk& operator=(const PhysicalDeviceVk& Source) = delete;
		PhysicalDeviceVk& operator=(PhysicalDeviceVk&& Right) noexcept = delete;

		virtual const Elysium::Core::Utf8String GetName() const override;
		virtual const PhysicalDeviceType GetDeviceType() const override;

		const PhysicalDevicePropertiesVk& GetProperties() const;
		const PhysicalDeviceFeaturesVk& GetFeatures() const;
		const Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk> GetQueueFamilyProperties() const;
		const Elysium::Core::Collections::Template::Array<ExtensionPropertyVk> GetAvailableExtensions() const;
	private:
		PhysicalDeviceVk();

		const bool SupportsPresentation(const VkSurfaceKHR NativeSurfaceHandle, const Elysium::Core::uint32_t FamilyIndex) const;

		VkPhysicalDevice _NativePhysicalDeviceHandle;
		PhysicalDevicePropertiesVk _Properties;
		PhysicalDeviceFeaturesVk _Features;
		VkPhysicalDeviceMemoryProperties _NativeMemoryProperties;
	};
}
#endif
