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

void Elysium::Graphics::Rendering::CommandBuffer::RecordBeginRenderPass(const RenderPass& RenderPass, const FrameBuffer& FrameBuffer,
	const Color& ClearColor, const float Depth, const Elysium::Core::uint32_t Stencil)
{
	_NativeCommandBuffer->RecordBeginRenderPass(*RenderPass._NativeRenderPass, *FrameBuffer._NativeFrameBuffer, ClearColor, Depth, Stencil);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordEndRenderPass()
{
	_NativeCommandBuffer->RecordEndRenderPass();
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordSetGraphicsPipeline(const GraphicsPipeline& GraphicsPipeline)
{
	_NativeCommandBuffer->RecordSetGraphicsPipeline(*GraphicsPipeline._NativeGraphicsPipeline);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordSetVertexBuffer(const VertexBuffer& VertexBuffer)
{
	_NativeCommandBuffer->RecordSetVertexBuffer(*VertexBuffer._NativeVertexBuffer);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordSetIndexBuffer(const IndexBuffer& IndexBuffer)
{
	_NativeCommandBuffer->RecordSetIndexBuffer(*IndexBuffer._NativeIndexBuffer);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordDrawPrimitives(const Elysium::Core::uint32_t VertexCount, const Elysium::Core::uint32_t InstanceCount, const Elysium::Core::uint32_t FirstVertex, const Elysium::Core::uint32_t FirstInstance)
{
	_NativeCommandBuffer->RecordDrawPrimitives(VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordDrawIndexedPrimitives(const PrimitiveType PrimitiveType, const Elysium::Core::uint32_t BaseVertex, const Elysium::Core::uint32_t MinimumVertexIndex, const Elysium::Core::uint32_t NumberVertices, const Elysium::Core::uint32_t StartIndex, const Elysium::Core::uint32_t NumberIndices)
{
	_NativeCommandBuffer->RecordDrawIndexedPrimitives(PrimitiveType, BaseVertex, MinimumVertexIndex, NumberVertices, StartIndex, NumberIndices);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordBlit(const FrameBuffer& FrameBuffer, const BlitFilter Filter)
{
	_NativeCommandBuffer->RecordBlit(*FrameBuffer._NativeFrameBuffer, Filter);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordClearBackBufferColorImage(const Color ClearColor)
{
	_NativeCommandBuffer->RecordClearBackBufferColorImage(ClearColor);
}

void Elysium::Graphics::Rendering::CommandBuffer::RecordClearBackBufferDepthImage(const float Depth, const Elysium::Core::uint32_t Stencil)
{
	_NativeCommandBuffer->RecordClearBackBufferDepthImage(Depth, Stencil);
}

Elysium::Graphics::Rendering::CommandBuffer::CommandBuffer(Native::INativeCommandBuffer* NativeCommandBuffer)
	: _NativeCommandBuffer(NativeCommandBuffer)
{ }
