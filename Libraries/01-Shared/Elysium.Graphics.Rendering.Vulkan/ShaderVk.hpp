/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESHADER
#include "../Elysium.Graphics/INativeShader.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API ShaderVk final : public INativeShader
	{
	public:
		ShaderVk(const LogicalDeviceVk& LogicalDevice);
		ShaderVk(const ShaderVk& Source) = delete;
		ShaderVk(ShaderVk&& Right) noexcept = delete;
		virtual ~ShaderVk();

		ShaderVk& operator=(const ShaderVk& Source) = delete;
		ShaderVk& operator=(ShaderVk&& Right) noexcept = delete;
	private:
		const LogicalDeviceVk& _LogicalDevice;
		VkShaderModule _NativeShaderModule;

		VkShaderModule CreateShaderModule();
	};
}
#endif
