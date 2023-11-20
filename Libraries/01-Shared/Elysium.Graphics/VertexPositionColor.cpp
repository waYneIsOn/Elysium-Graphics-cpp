#include "VertexPositionColor.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

const Elysium::Graphics::Rendering::VertexDeclaration Elysium::Graphics::Rendering::VertexPositionColor::_Declaration = CreateVertexDeclaration();

Elysium::Graphics::Rendering::VertexPositionColor::VertexPositionColor()
	: Position(0.0f, 0.0f, 0.0f), Color(Color.Red)
{ }

Elysium::Graphics::Rendering::VertexPositionColor::VertexPositionColor(const Elysium::Core::Math::Numerics::Vector3<float>& Position, const Elysium::Graphics::Color Color)
	: Position(Position), Color(Color)
{ }

Elysium::Graphics::Rendering::VertexPositionColor::VertexPositionColor(const VertexPositionColor & Source)
	: Position(Source.Position), Color(Source.Color)
{ }

Elysium::Graphics::Rendering::VertexPositionColor::~VertexPositionColor()
{ }

Elysium::Graphics::Rendering::VertexPositionColor& Elysium::Graphics::Rendering::VertexPositionColor::operator=(const VertexPositionColor& Source)
{
	if (this != &Source)
	{
		Position = Source.Position;
		Color = Source.Color;
	}
	return *this;
}

const Elysium::Graphics::Rendering::VertexDeclaration& Elysium::Graphics::Rendering::VertexPositionColor::GetVertexDeclaration() const
{
	return _Declaration;
}

const Elysium::Graphics::Rendering::VertexDeclaration Elysium::Graphics::Rendering::VertexPositionColor::CreateVertexDeclaration()
{
	Elysium::Core::Template::Container::Vector<VertexElement> Elements =
	{
		VertexElement(0, VertexElementFormat::Vector3Single, VertexElementUsage::Position, 0),
		VertexElement(12, VertexElementFormat::Color, VertexElementUsage::Color, 0),
	};

	return VertexDeclaration(16, Elysium::Core::Template::Functional::Move(Elements));
}

