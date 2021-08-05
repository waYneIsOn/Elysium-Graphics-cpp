#include "KeyboardState.hpp"

Elysium::Graphics::Input::KeyboardState::~KeyboardState()
{ }

const bool Elysium::Graphics::Input::KeyboardState::IsKeyDown(const Key Key) const
{
	return _States[static_cast<Elysium::Core::uint32_t>(Key)] == KeyState::Down;
}

const bool Elysium::Graphics::Input::KeyboardState::IsKeyUp(const Key Key) const
{
	return _States[static_cast<Elysium::Core::uint32_t>(Key)] == KeyState::Up;
}

Elysium::Graphics::Input::KeyboardState::KeyboardState()
	: _States()
{ }
