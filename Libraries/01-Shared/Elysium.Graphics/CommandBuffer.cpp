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

void Elysium::Graphics::Rendering::CommandBuffer::RecordSecondaryBuffer(const CommandBuffer& CommandBuffer)
{
	_NativeCommandBuffer->RecordSecondaryBuffer(*CommandBuffer._NativeCommandBuffer);
}

void Elysium::Graphics::Rendering::CommandBuffer::BeginRenderPass(const RenderPass& RenderPass, const FrameBuffer& FrameBuffer)
{
	_NativeCommandBuffer->BeginRenderPass(RenderPass._NativeRenderPass, FrameBuffer._NativeFrameBuffer);
}

void Elysium::Graphics::Rendering::CommandBuffer::EndRenderPass()
{
	_NativeCommandBuffer->EndRenderPass();
}

void Elysium::Graphics::Rendering::CommandBuffer::SetGraphicsPipeline(const GraphicsPipeline& GraphicsPipeline)
{
	_NativeCommandBuffer->SetGraphicsPipeline(*GraphicsPipeline._NativeGraphicsPipeline);
}

void Elysium::Graphics::Rendering::CommandBuffer::Draw(Elysium::Core::uint32_t VertexCount, Elysium::Core::uint32_t InstanceCount, Elysium::Core::uint32_t FirstVertex, Elysium::Core::uint32_t FirstInstance)
{
	_NativeCommandBuffer->Draw(VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void Elysium::Graphics::Rendering::CommandBuffer::ClearBackBufferImage(const Color ClearColor)
{
	_NativeCommandBuffer->ClearBackBufferImage(ClearColor);
}

void Elysium::Graphics::Rendering::CommandBuffer::ClearDepthImage(const float Depth, const Elysium::Core::int32_t Stencil)
{
	_NativeCommandBuffer->ClearDepthImage(Depth, Stencil);
}

Elysium::Graphics::Rendering::CommandBuffer::CommandBuffer(Native::INativeCommandBuffer* NativeCommandBuffer)
	: _NativeCommandBuffer(NativeCommandBuffer)
{ }
