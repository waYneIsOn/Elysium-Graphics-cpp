#include "GraphicsPipeline.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSDEVICE
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

void Elysium::Graphics::Rendering::GraphicsPipeline::AddShaderModule(const ShaderModule& ShaderModule, const ShaderModuleType Type)
{
	_NativeGraphicsPipeline->AddShaderModule(*ShaderModule._NativeShaderModule, Type);
}

void Elysium::Graphics::Rendering::GraphicsPipeline::Build(const RenderPass& RenderPass)
{
	_NativeGraphicsPipeline->Build(RenderPass._NativeRenderPass);
}
