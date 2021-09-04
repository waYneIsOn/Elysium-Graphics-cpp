#include "IndexBuffer.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::Rendering::IndexBuffer::IndexBuffer(const GraphicsDevice& GraphicsDevice, const IndexElementSize ElementSize, const Elysium::Core::uint32_t IndexCount, const BufferUsage Usage)
	: _GraphicsDevice(GraphicsDevice), _NativeIndexBuffer(_GraphicsDevice._NativeGraphicsDevice.CreateIndexBuffer(ElementSize, IndexCount, Usage))
{ }
Elysium::Graphics::Rendering::IndexBuffer::~IndexBuffer()
{
	if (_NativeIndexBuffer != nullptr)
	{
		delete _NativeIndexBuffer;
		_NativeIndexBuffer = nullptr;
	}
}

const Elysium::Graphics::Rendering::BufferUsage Elysium::Graphics::Rendering::IndexBuffer::GetBufferUsage() const
{
	return _NativeIndexBuffer->GetBufferUsage();
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::IndexBuffer::GetIndexCount() const
{
	return _NativeIndexBuffer->GetIndexCount();
}

const Elysium::Graphics::Rendering::IndexElementSize Elysium::Graphics::Rendering::IndexBuffer::GetIndexElementSize() const
{
	return _NativeIndexBuffer->GetIndexElementSize();
}

void Elysium::Graphics::Rendering::IndexBuffer::SetData(const void* First, const size_t Length)
{
	if (First == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}

	_NativeIndexBuffer->SetData(First, Length);
}
