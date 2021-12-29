#include "VertexElement.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

Elysium::Graphics::Rendering::VertexElement::VertexElement(const Elysium::Core::uint32_t Offset, const VertexElementFormat Format, const VertexElementUsage Usage, const Elysium::Core::uint32_t UsageIndex)
	: _Offset(Offset), _Format(Format), _Usage(Usage), _UsageIndex(UsageIndex)
{ }
Elysium::Graphics::Rendering::VertexElement::VertexElement(const VertexElement & Source)
	: _Offset(Source._Offset), _Format(Source._Format), _Usage(Source._Usage), _UsageIndex(Source._UsageIndex)
{ }
Elysium::Graphics::Rendering::VertexElement::VertexElement(VertexElement && Right) noexcept
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}
Elysium::Graphics::Rendering::VertexElement::~VertexElement()
{ }

Elysium::Graphics::Rendering::VertexElement::VertexElement()
	: _Offset(0), _Format(VertexElementFormat::Single), _Usage(VertexElementUsage::Position), _UsageIndex(0)
{ }

Elysium::Graphics::Rendering::VertexElement& Elysium::Graphics::Rendering::VertexElement::operator=(const VertexElement & Source)
{
	if (this != &Source)
	{
		_Offset = Source._Offset;
		_Format = Source._Format;
		_Usage = Source._Usage;
		_UsageIndex = Source._UsageIndex;
	}
	return *this;
}

Elysium::Graphics::Rendering::VertexElement& Elysium::Graphics::Rendering::VertexElement::operator=(VertexElement&& Right) noexcept
{
	if (this != &Right)
	{
		_Offset = Right._Offset;
		_Format = Right._Format;
		_Usage = Right._Usage;
		_UsageIndex = Right._UsageIndex;

		Right._Offset = 0;
		Right._Format = VertexElementFormat::Single;
		Right._Usage = VertexElementUsage::Position;
		Right._UsageIndex = 0;
	}
	return *this;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::VertexElement::GetOffset() const
{
	return _Offset;
}

const Elysium::Graphics::Rendering::VertexElementFormat Elysium::Graphics::Rendering::VertexElement::GetFormat() const
{
	return _Format;
}

const Elysium::Graphics::Rendering::VertexElementUsage Elysium::Graphics::Rendering::VertexElement::GetUsage() const
{
	return _Usage;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::VertexElement::GetUsageIndex() const
{
	return _UsageIndex;
}

void Elysium::Graphics::Rendering::VertexElement::SetOffset(const Elysium::Core::uint32_t Value)
{
	_Offset = Value;
}

void Elysium::Graphics::Rendering::VertexElement::SetFormat(const VertexElementFormat Value)
{
	_Format = Value;
}

void Elysium::Graphics::Rendering::VertexElement::SetUsage(const VertexElementUsage Value)
{
	_Usage = Value;
}

void Elysium::Graphics::Rendering::VertexElement::SetUsageIndex(const Elysium::Core::uint32_t Value)
{
	_UsageIndex = Value;
}
