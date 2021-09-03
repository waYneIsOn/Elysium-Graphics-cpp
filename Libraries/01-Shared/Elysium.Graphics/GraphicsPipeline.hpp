/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSPIPELINE
#define ELYSIUM_GRAPHICS_RENDERING_GRAPHICSPIPELINE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSPIPELINE
#include "INativeGraphicsPipeline.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_RENDERPASS
#include "RenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SHADERMODULE
#include "ShaderModule.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXBUFFER
#include "VertexBuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;

	class ELYSIUM_GRAPHICS_API GraphicsPipeline final
	{
		friend class CommandBuffer;
	public:
		GraphicsPipeline(const GraphicsDevice& GraphicsDevice);
		GraphicsPipeline(const GraphicsPipeline& Source) = delete;
		GraphicsPipeline(GraphicsPipeline&& Right) noexcept = delete;
		~GraphicsPipeline();

		GraphicsPipeline& operator=(const GraphicsPipeline& Source) = delete;
		GraphicsPipeline& operator=(GraphicsPipeline&& Right) noexcept = delete;

		RasterizerState& GetRasterizerState();

		void AddViewport(const Elysium::Core::uint32_t X, const Elysium::Core::uint32_t Y, const Elysium::Core::uint32_t Width,
			const Elysium::Core::uint32_t Height, const float MinimumDepth, const float MaximumDepth);
		void ClearViewports();

		void AddScissorRectangle(const Elysium::Core::int32_t X, const Elysium::Core::int32_t Y, const Elysium::Core::uint32_t Width,
			const Elysium::Core::uint32_t Height);
		void ClearScissorRectangles();

		void AddShaderModule(const ShaderModule& ShaderModule, const ShaderModuleType Type);
		void ClearShaderModules();

		void SetVertexBuffer(const VertexBuffer& VertexBuffer);
		void SetVertexBuffer(const VertexBuffer& VertexBuffer, const Elysium::Core::uint32_t VertexOffset);

		void Build(const RenderPass& RenderPass);
	private:
		const GraphicsDevice& _GraphicsDevice;

		Native::INativeGraphicsPipeline* _NativeGraphicsPipeline;
	};
}
#endif
