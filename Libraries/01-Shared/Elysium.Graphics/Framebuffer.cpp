#include "FrameBuffer.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::Rendering::FrameBuffer::FrameBuffer(const GraphicsDevice& GraphicsDevice, const RenderPass& RenderPass)
	: _GraphicsDevice(GraphicsDevice), _NativeFrameBuffer(_GraphicsDevice._NativeGraphicsDevice.CreateFrameBuffer(*RenderPass._NativeRenderPass))
{ }
Elysium::Graphics::Rendering::FrameBuffer::~FrameBuffer()
{
	if (_NativeFrameBuffer != nullptr)
	{
		delete _NativeFrameBuffer;
		_NativeFrameBuffer = nullptr;
	}
}
