#include "RenderPass.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::Rendering::RenderPass::RenderPass(const GraphicsDevice& GraphicsDevice)
	: _GraphicsDevice(GraphicsDevice), _NativeRenderPass(_GraphicsDevice._NativeGraphicsDevice.CreateRenderPass())
{ }
Elysium::Graphics::Rendering::RenderPass::~RenderPass()
{
	if (_NativeRenderPass != nullptr)
	{
		delete _NativeRenderPass;
		_NativeRenderPass = nullptr;
	}
}

