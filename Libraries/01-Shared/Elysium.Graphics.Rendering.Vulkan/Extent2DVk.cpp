#include "Extent2DVk.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::Extent2DVk::Extent2DVk()
	: Width(0), Height(0)
{ }
Elysium::Graphics::Rendering::Vulkan::Extent2DVk::Extent2DVk(Elysium::Core::uint32_t Width, Elysium::Core::uint32_t Height)
	: Width(Width), Height(Height)
{ }
Elysium::Graphics::Rendering::Vulkan::Extent2DVk::Extent2DVk(const Extent2DVk& Source)
	: Width(Source.Width), Height(Source.Height)
{ }
Elysium::Graphics::Rendering::Vulkan::Extent2DVk::Extent2DVk(Extent2DVk&& Right) noexcept
	: Width(0), Height(0)
{
	*this = std::move(Right);
}
Elysium::Graphics::Rendering::Vulkan::Extent2DVk::~Extent2DVk()
{ }

Elysium::Graphics::Rendering::Vulkan::Extent2DVk& Elysium::Graphics::Rendering::Vulkan::Extent2DVk::operator=(const Extent2DVk& Source)
{
	if (this != &Source)
	{
		Width = Source.Width;
		Height = Source.Height;
	}
	return *this;
}

Elysium::Graphics::Rendering::Vulkan::Extent2DVk& Elysium::Graphics::Rendering::Vulkan::Extent2DVk::operator=(Extent2DVk&& Right) noexcept
{
	if (this != &Right)
	{
		Width = Right.Width;
		Height = Right.Height;

		Right.Width = 0;
		Right.Height = 0;
	}
	return *this;
}
