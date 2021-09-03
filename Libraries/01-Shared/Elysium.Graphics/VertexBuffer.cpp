#include "VertexBuffer.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::Rendering::VertexBuffer::VertexBuffer(const GraphicsDevice& GraphicsDevice, const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount, const BufferUsage Usage)
	: _GraphicsDevice(GraphicsDevice), _NativeVertexBuffer(_GraphicsDevice._NativeGraphicsDevice.CreateVertexBuffer(Declaration, VertexCount, Usage))
{ }
Elysium::Graphics::Rendering::VertexBuffer::~VertexBuffer()
{
	if (_NativeVertexBuffer != nullptr)
	{
		delete _NativeVertexBuffer;
		_NativeVertexBuffer = nullptr;
	}
}

const Elysium::Graphics::Rendering::BufferUsage Elysium::Graphics::Rendering::VertexBuffer::GetBufferUsage() const
{
	return _NativeVertexBuffer->GetBufferUsage();
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::VertexBuffer::GetVertexCount() const
{
	return _NativeVertexBuffer->GetVertexCount();
}

const Elysium::Graphics::Rendering::VertexDeclaration& Elysium::Graphics::Rendering::VertexBuffer::GetVertexDeclaration() const
{
	return _NativeVertexBuffer->GetVertexDeclaration();
}

void Elysium::Graphics::Rendering::VertexBuffer::SetData(const void* First, const size_t Length)
{
	if (First == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}

	_NativeVertexBuffer->SetData(First, Length);
}
