#include "RenderPass.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::Rendering::RenderPass::RenderPass(const GraphicsDevice & GraphicsDevice, const SurfaceFormat SurfaceFormat)
	: _GraphicsDevice(GraphicsDevice), _NativeRenderPass(_GraphicsDevice._NativeGraphicsDevice.CreateRenderPass(SurfaceFormat))
{ }
Elysium::Graphics::Rendering::RenderPass::~RenderPass()
{
	if (_NativeRenderPass != nullptr)
	{
		delete _NativeRenderPass;
		_NativeRenderPass = nullptr;
	}
}

const Elysium::Graphics::Rendering::SurfaceFormat Elysium::Graphics::Rendering::RenderPass::GetSurfaceFormat() const
{
	return _NativeRenderPass->GetSurfaceFormat();
}

