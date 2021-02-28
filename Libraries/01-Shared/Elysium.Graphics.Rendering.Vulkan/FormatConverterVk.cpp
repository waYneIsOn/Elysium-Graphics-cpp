#include "FormatConverterVk.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/NotImplementedException.hpp"
#endif

const VkFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const SurfaceFormat Format)
{
	switch (Format)
	{
	case SurfaceFormat::Undefined:
		return VkFormat::VK_FORMAT_UNDEFINED;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled SurfaceFormat.");
	}
}

const VkFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const DepthFormat Format)
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
