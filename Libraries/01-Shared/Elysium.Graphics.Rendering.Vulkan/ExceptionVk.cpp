#include "ExceptionVk.hpp"

Elysium::Graphics::Rendering::Vulkan::ExceptionVk::ExceptionVk(const VkResult Result)
	: _Result(Result)
{ }
Elysium::Graphics::Rendering::Vulkan::ExceptionVk::~ExceptionVk()
{ }
