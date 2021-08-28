#include "SwapchainFrameBufferVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTER
#include "FormatConverterVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::SwapchainFrameBufferVk::~SwapchainFrameBufferVk()
{ }

Elysium::Graphics::Rendering::Vulkan::SwapchainFrameBufferVk::SwapchainFrameBufferVk(const GraphicsDeviceVk& GraphicsDevice)
	: _GraphicsDevice(GraphicsDevice)
{ }

const Elysium::Graphics::Rendering::SurfaceFormat Elysium::Graphics::Rendering::Vulkan::SwapchainFrameBufferVk::GetSurfaceFormat() const
{
	return FormatConverterVk::Convert(_GraphicsDevice._SelectedNativeSurfaceFormat.format);
}
