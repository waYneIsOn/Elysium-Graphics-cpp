/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API ExceptionVk : public Core::Exception
	{
	public:
		ExceptionVk() = delete;
		ExceptionVk(const char8_t* Message) = delete;
		ExceptionVk(Elysium::Core::String&& Message) = delete;
		ExceptionVk(const VkResult Result);
		virtual ~ExceptionVk();
	private:
		const VkResult _Result;
	};
}
#endif
