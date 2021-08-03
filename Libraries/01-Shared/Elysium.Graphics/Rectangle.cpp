#include "Rectangle.hpp"

Elysium::Graphics::Rendering::Rectangle::~Rectangle()
{ }

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Rectangle::GetBottom() const
{
	return _NativeRectangle.GetBottom();
}

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Rectangle::GetLeft() const
{
	return _NativeRectangle.GetLeft();
}

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Rectangle::GetRight() const
{
	return _NativeRectangle.GetRight();
}

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Rectangle::GetTop() const
{
	return _NativeRectangle.GetTop();
}

const Elysium::Core::int32_t& Elysium::Graphics::Rendering::Rectangle::GetX() const
{
	return _NativeRectangle.GetX();
}

const Elysium::Core::int32_t& Elysium::Graphics::Rendering::Rectangle::GetY() const
{
	return _NativeRectangle.GetY();
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Rectangle::GetWidth() const
{
	return _NativeRectangle.GetWidth();
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Rectangle::GetHeight() const
{
	return _NativeRectangle.GetHeight();
}

void Elysium::Graphics::Rendering::Rectangle::SetX(const Elysium::Core::int32_t Value)
{
	_NativeRectangle.SetX(Value);
}

void Elysium::Graphics::Rendering::Rectangle::SetY(const Elysium::Core::int32_t Value)
{
	_NativeRectangle.SetY(Value);
}

void Elysium::Graphics::Rendering::Rectangle::SetWidth(const Elysium::Core::int32_t Value)
{
	_NativeRectangle.SetWidth(Value);
}

void Elysium::Graphics::Rendering::Rectangle::SetHeight(const Elysium::Core::int32_t Value)
{
	_NativeRectangle.SetHeight(Value);
}

Elysium::Graphics::Rendering::Rectangle::Rectangle(INativeRectangle & NativeRectangle)
	: _NativeRectangle(NativeRectangle)
{ }
