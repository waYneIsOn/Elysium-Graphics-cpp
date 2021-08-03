#include "CommandBuffer.hpp"

Elysium::Graphics::Rendering::CommandBuffer::~CommandBuffer()
{
	if (_NativeCommandBuffer != nullptr)
	{
		delete _NativeCommandBuffer;
		_NativeCommandBuffer = nullptr;
	}
}

void Elysium::Graphics::Rendering::CommandBuffer::Begin()
{
	_NativeCommandBuffer->Begin();
}

void Elysium::Graphics::Rendering::CommandBuffer::End()
{
	_NativeCommandBuffer->End();
}

void Elysium::Graphics::Rendering::CommandBuffer::Reset()
{
	_NativeCommandBuffer->Reset();
}

void Elysium::Graphics::Rendering::CommandBuffer::BeginRenderPass(const RenderPass& RenderPass, const Framebuffer& Framebuffer)
{
	_NativeCommandBuffer->BeginRenderPass(RenderPass._NativeRenderPass, Framebuffer._NativeFramebuffer);
}

void Elysium::Graphics::Rendering::CommandBuffer::EndRenderPass()
{
	_NativeCommandBuffer->EndRenderPass();
}

void Elysium::Graphics::Rendering::CommandBuffer::ClearBackBufferImage(const Color ClearColor)
{
	_NativeCommandBuffer->ClearBackBufferImage(ClearColor);
}

void Elysium::Graphics::Rendering::CommandBuffer::ClearDepthImage(const float Depth, const Elysium::Core::int32_t Stencil)
{
	_NativeCommandBuffer->ClearDepthImage(Depth, Stencil);
}

Elysium::Graphics::Rendering::CommandBuffer::CommandBuffer(INativeCommandBuffer* NativeCommandBuffer)
	: _NativeCommandBuffer(NativeCommandBuffer)
{ }
