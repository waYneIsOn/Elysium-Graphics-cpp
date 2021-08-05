/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_SHADERMODULE
#define ELYSIUM_GRAPHICS_RENDERING_SHADERMODULE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/ArrayOfByte.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESHADERMODULE
#include "INativeShaderModule.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API ShaderModule final
	{
	public:
		ShaderModule(const GraphicsDevice& GraphicsDevice, const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Data);
		ShaderModule(const ShaderModule& Source) = delete;
		ShaderModule(ShaderModule&& Right) noexcept = delete;
		~ShaderModule();

		ShaderModule& operator=(const ShaderModule& Source) = delete;
		ShaderModule& operator=(ShaderModule&& Right) noexcept = delete;
	private:
		const GraphicsDevice& _GraphicsDevice;

		//INativeShaderModule& _NativeShaderModule;
	};
}
#endif
