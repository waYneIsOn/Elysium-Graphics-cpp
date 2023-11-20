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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
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
		friend class Elysium::Core::Template::Container::Vector<PhysicalDeviceVk>;
		friend class DepthBufferVk;
		friend class FrameBufferVk;
		friend class GraphicsDeviceVk;
		friend class GraphicsInstanceVk;
		friend class IndexBufferVk;
		friend class VertexBufferVk;
	private:
		PhysicalDeviceVk();
	public:
		PhysicalDeviceVk(const PhysicalDeviceVk& Source) = delete;

		PhysicalDeviceVk(PhysicalDeviceVk&& Right) noexcept = delete;

		virtual ~PhysicalDeviceVk();
	public:
		PhysicalDeviceVk& operator=(const PhysicalDeviceVk& Source) = delete;

		PhysicalDeviceVk& operator=(PhysicalDeviceVk&& Right) noexcept = delete;
	public:
		virtual const Elysium::Core::Utf8String GetName() const override;

		virtual const PhysicalDeviceType GetDeviceType() const override;

		const PhysicalDevicePropertiesVk& GetProperties() const;

		const PhysicalDeviceFeaturesVk& GetFeatures() const;

		const Elysium::Core::Template::Container::Vector<QueueFamilyPropertyVk> GetQueueFamilyProperties() const;

		const Elysium::Core::Template::Container::Vector<ExtensionPropertyVk> GetAvailableExtensions() const;
	private:
		const bool SupportsPresentation(const VkSurfaceKHR NativeSurfaceHandle, const Elysium::Core::uint32_t FamilyIndex) const;
	private:
		VkPhysicalDevice _NativePhysicalDeviceHandle;
		PhysicalDevicePropertiesVk _Properties;
		PhysicalDeviceFeaturesVk _Features;
		VkPhysicalDeviceMemoryProperties _NativeMemoryProperties;
	};
}
#endif
