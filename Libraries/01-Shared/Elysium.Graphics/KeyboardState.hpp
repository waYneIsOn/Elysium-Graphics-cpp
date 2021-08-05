/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_INPUT_KEYBOARDSTATE
#define ELYSIUM_GRAPHICS_INPUT_KEYBOARDSTATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_INPUT_KEY
#include "Key.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_INPUT_KEYSTATE
#include "KeyState.hpp"
#endif

namespace Elysium::Graphics::Input
{
	class ELYSIUM_GRAPHICS_API KeyboardState final
	{
	public:
		KeyboardState(const KeyboardState& Source) = delete;
		KeyboardState(KeyboardState&& Right) noexcept = delete;
		~KeyboardState();

		KeyboardState& operator=(const KeyboardState& Source) = delete;
		KeyboardState& operator=(KeyboardState&& Right) noexcept = delete;

		const bool IsKeyDown(const Key Key) const;
		const bool IsKeyUp(const Key Key) const;
	private:
		KeyboardState();

		const KeyState _States[1];
	};
}
#endif
