#include "CommandBuffer.hpp"

Elysium::Graphics::Rendering::CommandBuffer::~CommandBuffer()
{
	if (_NativeCommandBuffer != nullptr)
	{
		delete _NativeCommandBuffer;
		_NativeCommandBuffer = nullptr;
	}
}

void Elysium::Graphics::Rendering::CommandBuffer::BeginRecording()
{
	_NativeCommandBuffer->BeginRecording();
}

void Elysium::Graphics::Rendering::CommandBuffer::EndRecording()
{
	_NativeCommandBuffer->EndRecording();
}

void Elysium::Graphics::Rendering::CommandBuffer::Reset()
{
	_NativeCommandBuffer->Reset();
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordSecondaryBuffer(const CommandBuffer& CommandBuffer)
{
	_NativeCommandBuffer->RecordSecondaryBuffer(*CommandBuffer._NativeCommandBuffer);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordBeginRenderPass(const RenderPass& RenderPass, const FrameBuffer& FrameBuffer)
{
	_NativeCommandBuffer->RecordBeginRenderPass(*RenderPass._NativeRenderPass, *FrameBuffer._NativeFrameBuffer);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordEndRenderPass()
{
	_NativeCommandBuffer->RecordEndRenderPass();
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordSetGraphicsPipeline(const GraphicsPipeline& GraphicsPipeline)
{
	_NativeCommandBuffer->RecordSetGraphicsPipeline(*GraphicsPipeline._NativeGraphicsPipeline);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordDraw(Elysium::Core::uint32_t VertexCount, Elysium::Core::uint32_t InstanceCount, Elysium::Core::uint32_t FirstVertex, Elysium::Core::uint32_t FirstInstance)
{
	_NativeCommandBuffer->RecordDraw(VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordBlit(const FrameBuffer& FrameBuffer)
{
	_NativeCommandBuffer->RecordBlit(*FrameBuffer._NativeFrameBuffer);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordClearBackBufferColorImage(const Color ClearColor)
{
	_NativeCommandBuffer->RecordClearBackBufferColorImage(ClearColor);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordClearBackBufferDepthImage(const float Depth, const Elysium::Core::int32_t Stencil)
{
	_NativeCommandBuffer->RecordClearBackBufferDepthImage(Depth, Stencil);
}

Elysium::Graphics::Rendering::CommandBuffer::CommandBuffer(Native::INativeCommandBuffer* NativeCommandBuffer)
	: _NativeCommandBuffer(NativeCommandBuffer)
{ }
