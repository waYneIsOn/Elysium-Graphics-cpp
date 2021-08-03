#include "ViewportVk.hpp"

Elysium::Graphics::Rendering::Vulkan::ViewportVk::ViewportVk(const Elysium::Core::uint32_t X, const Elysium::Core::uint32_t Y, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height, const float MinimumDepth, const float MaximumDepth)
	: _NativeViewport()
{
	_NativeViewport.x = X;
	_NativeViewport.y = X;
	_NativeViewport.width = Width;
	_NativeViewport.height = Height;
	_NativeViewport.minDepth = MinimumDepth;
	_NativeViewport.maxDepth = MaximumDepth;
}
Elysium::Graphics::Rendering::Vulkan::ViewportVk::~ViewportVk()
{ }

const float Elysium::Graphics::Rendering::Vulkan::ViewportVk::GetX() const
{
	return _NativeViewport.x;
}

const float Elysium::Graphics::Rendering::Vulkan::ViewportVk::GetY() const
{
	return _NativeViewport.y;
}

const float Elysium::Graphics::Rendering::Vulkan::ViewportVk::GetWidth() const
{
	return _NativeViewport.width;
}

const float Elysium::Graphics::Rendering::Vulkan::ViewportVk::GetHeight() const
{
	return _NativeViewport.height;
}

const float Elysium::Graphics::Rendering::Vulkan::ViewportVk::GetMinDepth() const
{
	return _NativeViewport.minDepth;
}

const float Elysium::Graphics::Rendering::Vulkan::ViewportVk::GetMaxDepth() const
{
	return _NativeViewport.maxDepth;
}
