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

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESHADERMODULE
#include "INativeShaderModule.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;

	class ELYSIUM_GRAPHICS_API ShaderModule final
	{
		friend class GraphicsPipeline;
	public:
		ShaderModule(const GraphicsDevice& GraphicsDevice, Elysium::Core::Template::Container::Vector<Elysium::Core::byte>&& ByteCode);

		ShaderModule(const ShaderModule& Source) = delete;

		ShaderModule(ShaderModule&& Right) noexcept = delete;

		~ShaderModule();
	public:
		ShaderModule& operator=(const ShaderModule& Source) = delete;

		ShaderModule& operator=(ShaderModule&& Right) noexcept = delete;
	private:
		const GraphicsDevice& _GraphicsDevice;
		const Elysium::Core::Template::Container::Vector<Elysium::Core::byte> _ByteCode;

		Native::INativeShaderModule* _NativeShaderModule;
	};
}
#endif
