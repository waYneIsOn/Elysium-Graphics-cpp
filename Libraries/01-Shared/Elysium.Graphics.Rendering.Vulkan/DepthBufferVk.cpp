#include "DepthBufferVk.hpp"

Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::~DepthBufferVk()
{ }

Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::DepthBufferVk(const VkDevice NativeLogicalDeviceHandle)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle)
{ }
