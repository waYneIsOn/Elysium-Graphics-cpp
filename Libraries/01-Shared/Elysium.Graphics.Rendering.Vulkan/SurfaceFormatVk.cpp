#include "SurfaceFormatVk.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk::SurfaceFormatVk()
	: Format(FormatVk::Undefined), ColorSpace(ColorSpaceVk::SRGBNonLinear)
{ }
Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk::SurfaceFormatVk(const SurfaceFormatVk & Source)
	: Format(Source.Format), ColorSpace(Source.ColorSpace)
{ }
Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk::SurfaceFormatVk(SurfaceFormatVk&& Right) noexcept
	: Format(FormatVk::Undefined), ColorSpace(ColorSpaceVk::SRGBNonLinear)
{
	*this = std::move(Right);
}
Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk::~SurfaceFormatVk()
{ }

Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk& Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk::operator=(const SurfaceFormatVk & Source)
{
	if (this != &Source)
	{
		Format = Source.Format;
		ColorSpace = Source.ColorSpace;
	}
	return *this;
}

Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk& Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk::operator=(SurfaceFormatVk&& Right) noexcept
{
	if (this != &Right)
	{
		Format = Right.Format;
		ColorSpace = Right.ColorSpace;

		Right.Format = FormatVk::Undefined;
		Right.ColorSpace = ColorSpaceVk::SRGBNonLinear;
	}
	return *this;
}
