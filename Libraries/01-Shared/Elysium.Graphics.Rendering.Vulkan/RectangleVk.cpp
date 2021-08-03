#include "RectangleVk.hpp"

Elysium::Graphics::Rendering::Vulkan::RectangleVk::RectangleVk(const Elysium::Core::int32_t X, const Elysium::Core::int32_t Y, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height)
	: _NativeRectangle()
{
	_NativeRectangle.offset = { X, Y };
	_NativeRectangle.extent = { Width, Height };
}
Elysium::Graphics::Rendering::Vulkan::RectangleVk::~RectangleVk()
{ }

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Vulkan::RectangleVk::GetBottom() const
{
	return _NativeRectangle.offset.y + _NativeRectangle.extent.height;
}

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Vulkan::RectangleVk::GetLeft() const
{
	return _NativeRectangle.offset.x;
}

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Vulkan::RectangleVk::GetRight() const
{
	return _NativeRectangle.offset.x + _NativeRectangle.extent.width;
}

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Vulkan::RectangleVk::GetTop() const
{
	return _NativeRectangle.offset.y;
}

const Elysium::Core::int32_t& Elysium::Graphics::Rendering::Vulkan::RectangleVk::GetX() const
{
	return _NativeRectangle.offset.x;
}

const Elysium::Core::int32_t& Elysium::Graphics::Rendering::Vulkan::RectangleVk::GetY() const
{
	return _NativeRectangle.offset.y;
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Vulkan::RectangleVk::GetWidth() const
{
	return _NativeRectangle.extent.width;
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Vulkan::RectangleVk::GetHeight() const
{
	return _NativeRectangle.extent.height;
}

void Elysium::Graphics::Rendering::Vulkan::RectangleVk::SetX(const Elysium::Core::int32_t Value)
{
	_NativeRectangle.offset.x = Value;
}

void Elysium::Graphics::Rendering::Vulkan::RectangleVk::SetY(const Elysium::Core::int32_t Value)
{
	_NativeRectangle.offset.y = Value;
}

void Elysium::Graphics::Rendering::Vulkan::RectangleVk::SetWidth(const Elysium::Core::int32_t Value)
{
	_NativeRectangle.extent.width = Value;
}

void Elysium::Graphics::Rendering::Vulkan::RectangleVk::SetHeight(const Elysium::Core::int32_t Value)
{
	_NativeRectangle.extent.height = Value;
}
