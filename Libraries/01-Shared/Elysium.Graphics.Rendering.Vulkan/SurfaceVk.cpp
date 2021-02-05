#include "SurfaceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::SurfaceVk::~SurfaceVk()
{
	if (_NativeSurfaceHandle != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(_NativeInstanceHandle, _NativeSurfaceHandle, nullptr);
	}
}

const Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk Elysium::Graphics::Rendering::Vulkan::SurfaceVk::GetCapabilities(const PhysicalDeviceVk& PhysicalDevice)
{
	VkSurfaceCapabilitiesKHR NativeSurfaceCapabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &NativeSurfaceCapabilities);

	return SurfaceCapabilitiesVk(NativeSurfaceCapabilities);
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk> Elysium::Graphics::Rendering::Vulkan::SurfaceVk::GetFormats(const PhysicalDeviceVk& PhysicalDevice)
{
	uint32_t SurfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, nullptr);

	Elysium::Core::Collections::Template::Array<SurfaceFormatVk> SurfaceFormats =
		Elysium::Core::Collections::Template::Array<SurfaceFormatVk>(SurfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, (VkSurfaceFormatKHR*)&SurfaceFormats[0]);

	return SurfaceFormats;
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::PresentModeVk> Elysium::Graphics::Rendering::Vulkan::SurfaceVk::GetPresentModes(const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& PhysicalDevice)
{
	uint32_t PresentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, nullptr);

	Elysium::Core::Collections::Template::Array<PresentModeVk> PresentModes =
		Elysium::Core::Collections::Template::Array<PresentModeVk>(PresentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, (VkPresentModeKHR*)&PresentModes[0]);

	return PresentModes;
}

Elysium::Graphics::Rendering::Vulkan::SurfaceVk::SurfaceVk(const VkInstance NativeInstanceHandle, const VkSurfaceKHR NativeSurfaceHandle)
	: _NativeInstanceHandle(NativeInstanceHandle), _NativeSurfaceHandle(NativeSurfaceHandle)
{ }
