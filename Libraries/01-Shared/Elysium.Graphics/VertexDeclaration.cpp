#include "VertexDeclaration.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

Elysium::Graphics::Rendering::VertexDeclaration::VertexDeclaration(Elysium::Core::Collections::Template::Array<VertexElement>&& Elements)
	: _Stride(GetElementStride(Elements)), _Elements(Elysium::Core::Template::Functional::Move(Elements))
{ }
Elysium::Graphics::Rendering::VertexDeclaration::VertexDeclaration(const Elysium::Core::uint32_t Stride, Elysium::Core::Collections::Template::Array<VertexElement>&& Elements)
	: _Stride(Stride), _Elements(Elysium::Core::Template::Functional::Move(Elements))
{ }
Elysium::Graphics::Rendering::VertexDeclaration::~VertexDeclaration()
{ }

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::VertexDeclaration::GetVertexStride() const
{
	return _Stride;
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::VertexElement>& Elysium::Graphics::Rendering::VertexDeclaration::GetElements() const
{
	return _Elements;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::VertexDeclaration::GetElementStride(const Elysium::Core::Collections::Template::Array<VertexElement>& Elements)
{
	Elysium::Core::uint32_t Result = 0;

	for (size_t i = 0; i < Elements.GetLength(); i++)
	{
		Result += GetElementStride(Elements[i].GetFormat());
	}

	return Result;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::VertexDeclaration::GetElementStride(const VertexElementFormat Format)
{
	switch(Format)
	{
	case VertexElementFormat::NormalizedShort2:
	case VertexElementFormat::Byte4:
	case VertexElementFormat::Color:
	case VertexElementFormat::Short2:
	case VertexElementFormat::Single:
		return 4;
	case VertexElementFormat::Double:
	case VertexElementFormat::NormalizedShort4:
	case VertexElementFormat::Short4:
	case VertexElementFormat::Vector2Single:
		return 8;
	case VertexElementFormat::Vector3Single:
		return 12;
	case VertexElementFormat::Vector2Double:
	case VertexElementFormat::Vector4Single:
		return 16;
	case VertexElementFormat::Vector3Double:
		return 24;
	case VertexElementFormat::Vector4Double:
		return 32;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled VertexElementFormat.");
	}
}
