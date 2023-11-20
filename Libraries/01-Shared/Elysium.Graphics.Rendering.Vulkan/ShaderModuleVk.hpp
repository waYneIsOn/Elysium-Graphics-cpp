/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERMODULEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERMODULEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESHADERMODULE
#include "../Elysium.Graphics/INativeShaderModule.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API ShaderModuleVk final : public Native::INativeShaderModule
	{
		friend class GraphicsPipelineVk;
	public:
		ShaderModuleVk(const GraphicsDeviceVk& GraphicsDevice, const Elysium::Core::Template::Container::Vector<Elysium::Core::byte>& Data);
		ShaderModuleVk(const ShaderModuleVk& Source) = delete;
		ShaderModuleVk(ShaderModuleVk&& Right) noexcept = delete;
		virtual ~ShaderModuleVk();

		ShaderModuleVk& operator=(const ShaderModuleVk& Source) = delete;
		ShaderModuleVk& operator=(ShaderModuleVk&& Right) noexcept = delete;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		VkShaderModule _NativeShaderModule;

		VkShaderModule CreateShaderModule(const Elysium::Core::byte* Data, const size_t Length);
	};
}
#endif
