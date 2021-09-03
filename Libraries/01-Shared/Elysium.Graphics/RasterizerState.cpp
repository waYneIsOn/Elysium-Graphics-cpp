#include "RasterizerState.hpp"

Elysium::Graphics::Rendering::RasterizerState::RasterizerState()
{ }
Elysium::Graphics::Rendering::RasterizerState::~RasterizerState()
{ }

const Elysium::Graphics::Rendering::CullMode Elysium::Graphics::Rendering::RasterizerState::GetCullMode() const
{
	return _CullMode;
}

const Elysium::Graphics::Rendering::FillMode Elysium::Graphics::Rendering::RasterizerState::GetFillMode() const
{
	return _FillMode;
}

const float Elysium::Graphics::Rendering::RasterizerState::GetLineWidth() const
{
	return _LineWidth;
}

void Elysium::Graphics::Rendering::RasterizerState::SetCullMode(const CullMode Value)
{
	_CullMode = Value;
}

void Elysium::Graphics::Rendering::RasterizerState::SetFillMode(const FillMode Value)
{
	_FillMode = Value;
}

void Elysium::Graphics::Rendering::RasterizerState::SetLineWidth(const float Value)
{
	_LineWidth = Value;
}
