#include "FormatConverterVk.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Graphics::Rendering::PhysicalDeviceType Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const VkPhysicalDeviceType Value)
{
	switch (Value)
	{
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER:
		return PhysicalDeviceType::Other;
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		return PhysicalDeviceType::IntegratedGPU;
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		return PhysicalDeviceType::DiscreteGPU;
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		return PhysicalDeviceType::VirtualGPU;
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU:
		return PhysicalDeviceType::CPU;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled VkPhysicalDeviceType.");
	}
}

VkPresentModeKHR Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const PresentMode Value)
{
	switch (Value)
	{
	case PresentMode::Immediate:
		return VkPresentModeKHR::VK_PRESENT_MODE_IMMEDIATE_KHR;
	case PresentMode::VerticalSync:
		return VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled PresentMode.");
	}
}

VkFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const SurfaceFormat Value)
{
	switch (Value)
	{
	case SurfaceFormat::Undefined:
		return VkFormat::VK_FORMAT_UNDEFINED;
	case SurfaceFormat::B8G8R8A8_sRGB:
		return VkFormat::VK_FORMAT_B8G8R8A8_SRGB;
	case SurfaceFormat::R8G8B8A8_sRGB:
		return VkFormat::VK_FORMAT_R8G8B8A8_SRGB;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled SurfaceFormat.");
	}
}

VkFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const DepthFormat Value)
{
	switch (Value)
	{
	case DepthFormat::None:
		return VkFormat::VK_FORMAT_UNDEFINED;
	case DepthFormat::Depth16:
		return VkFormat::VK_FORMAT_D16_UNORM;
	case DepthFormat::Depth16Stencil8:
		return VkFormat::VK_FORMAT_D16_UNORM_S8_UINT;
	case DepthFormat::Depth24Stencil8:
		return VkFormat::VK_FORMAT_D24_UNORM_S8_UINT;
	case DepthFormat::Depth32:
		return VkFormat::VK_FORMAT_D32_SFLOAT;
	case DepthFormat::Depth32Stencil8:
		return VkFormat::VK_FORMAT_D32_SFLOAT_S8_UINT;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled DepthFormat.");
	}
}

VkFilter Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const BlitFilter Value)
{
	switch (Value)
	{
	case BlitFilter::Nearest:
		return VkFilter::VK_FILTER_NEAREST;
	case BlitFilter::Linear:
		return VkFilter::VK_FILTER_LINEAR;
	case BlitFilter::Cubic:
		return VkFilter::VK_FILTER_CUBIC_IMG;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled BlitFilter.");
	}
}

Elysium::Graphics::Rendering::SurfaceFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::ToSurfaceFormat(const VkFormat Value)
{
	switch (Value)
	{
	case VkFormat::VK_FORMAT_UNDEFINED:
		return SurfaceFormat::Undefined;
	case VkFormat::VK_FORMAT_B8G8R8A8_SRGB:
		return SurfaceFormat::B8G8R8A8_sRGB;
	case VkFormat::VK_FORMAT_R8G8B8A8_SRGB:
		return SurfaceFormat::R8G8B8A8_sRGB;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled VkFormat.");
	}
}

Elysium::Graphics::Rendering::DepthFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::ToDepthFormat(const VkFormat Value)
{
	switch (Value)
	{
	case VkFormat::VK_FORMAT_UNDEFINED:
		return DepthFormat::None;
	case VkFormat::VK_FORMAT_D16_UNORM:
		return DepthFormat::Depth16;
	case VkFormat::VK_FORMAT_D16_UNORM_S8_UINT:
		return DepthFormat::Depth16Stencil8;
	case VkFormat::VK_FORMAT_D24_UNORM_S8_UINT:
		return DepthFormat::Depth24Stencil8;
	case VkFormat::VK_FORMAT_D32_SFLOAT:
		return DepthFormat::Depth32;
	case VkFormat::VK_FORMAT_D32_SFLOAT_S8_UINT:
		return DepthFormat::Depth32Stencil8;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled VkFormat.");
	}
}
