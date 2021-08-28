#include "GraphicsPipeline.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::Rendering::GraphicsPipeline::GraphicsPipeline(const GraphicsDevice& GraphicsDevice)
	: _GraphicsDevice(GraphicsDevice), _NativeGraphicsPipeline(_GraphicsDevice._NativeGraphicsDevice.CreateGraphicsPipeline())
{ }
Elysium::Graphics::Rendering::GraphicsPipeline::~GraphicsPipeline()
{
	if (_NativeGraphicsPipeline != nullptr)
	{
		delete _NativeGraphicsPipeline;
		_NativeGraphicsPipeline = nullptr;
	}
}

void Elysium::Graphics::Rendering::GraphicsPipeline::AddViewport(const Elysium::Core::uint32_t X, const Elysium::Core::uint32_t Y, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height, const float MinimumDepth, const float MaximumDepth)
{
	_NativeGraphicsPipeline->AddViewport(X, Y, Width, Height, MinimumDepth, MaximumDepth);
}

void Elysium::Graphics::Rendering::GraphicsPipeline::ClearViewports()
{
	_NativeGraphicsPipeline->ClearViewports();
}

void Elysium::Graphics::Rendering::GraphicsPipeline::AddScissorRectangle(const Elysium::Core::int32_t X, const Elysium::Core::int32_t Y, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height)
{
	_NativeGraphicsPipeline->AddScissorRectangle(X, Y, Width, Height);
}

void Elysium::Graphics::Rendering::GraphicsPipeline::ClearScissorRectangles()
{
	_NativeGraphicsPipeline->ClearScissorRectangles();
}

void Elysium::Graphics::Rendering::GraphicsPipeline::AddShaderModule(const ShaderModule& ShaderModule, const ShaderModuleType Type)
{
	_NativeGraphicsPipeline->AddShaderModule(*ShaderModule._NativeShaderModule, Type);
}

void Elysium::Graphics::Rendering::GraphicsPipeline::Build(const RenderPass& RenderPass)
{
	_NativeGraphicsPipeline->Build(*RenderPass._NativeRenderPass);
}
