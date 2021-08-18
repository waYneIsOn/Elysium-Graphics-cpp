#include "VertexDeclaration.hpp"

Elysium::Graphics::Rendering::VertexDeclaration::VertexDeclaration(const Elysium::Core::uint32_t Stride)
	: _Stride(Stride)
{ }
Elysium::Graphics::Rendering::VertexDeclaration::~VertexDeclaration()
{ }

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::VertexDeclaration::GetVertexStride() const
{
	return _Stride;
}
