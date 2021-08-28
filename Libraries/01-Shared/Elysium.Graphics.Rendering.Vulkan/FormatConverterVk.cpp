#include "FormatConverterVk.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/NotImplementedException.hpp"
#endif

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

VkFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const SurfaceFormat Format)
{
	switch (Format)
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

VkFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const DepthFormat Format)
{
	switch (Format)
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

Elysium::Graphics::Rendering::SurfaceFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const VkFormat Format)
{
	switch (Format)
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
