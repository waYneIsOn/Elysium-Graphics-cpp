/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSPIPELINE
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSPIPELINE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_RASTERIZERSTATE
#include "RasterizerState.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEINDEXBUFFER
#include "INativeIndexBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVERENDERPASS
#include "INativeRenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESHADERMODULE
#include "INativeShaderModule.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEVERTEXBUFFER
#include "INativeVertexBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SHADERMODULETYPE
#include "ShaderModuleType.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeGraphicsPipeline
	{
	public:
		virtual ~INativeGraphicsPipeline() { }

		virtual RasterizerState& GetRasterizerState() = 0;

		virtual void AddViewport(const Elysium::Core::uint32_t X, const Elysium::Core::uint32_t Y, const Elysium::Core::uint32_t Width, 
			const Elysium::Core::uint32_t Height, const float MinimumDepth, const float MaximumDepth) = 0;
		virtual void ClearViewports() = 0;

		virtual void AddScissorRectangle(const Elysium::Core::int32_t X, const Elysium::Core::int32_t Y, const Elysium::Core::uint32_t Width,
			const Elysium::Core::uint32_t Height) = 0;
		virtual void ClearScissorRectangles() = 0;

		virtual void AddShaderModule(const INativeShaderModule& ShaderModule, const ShaderModuleType Type) = 0;
		virtual void ClearShaderModules() = 0;

		virtual void SetVertexBuffer(const INativeVertexBuffer& VertexBuffer, const Elysium::Core::uint32_t VertexOffset) = 0;

		virtual void Build(const INativeRenderPass& RenderPass) = 0;
	};
}
#endif
