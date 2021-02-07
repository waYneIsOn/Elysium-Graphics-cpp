#include "FormatConverterVk.hpp"

const VkFormat Elysium::Graphics::Rendering::Vulkan::FormatConverterVk::Convert(const SurfaceFormat& Format)
{
	switch (Format)
	{
	case SurfaceFormat::Undefined:
		return VkFormat::VK_FORMAT_UNDEFINED;
	default:
		// ToDo: throw specfici exception
		throw 1;
	}
}
