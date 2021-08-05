/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_INPUT_INPUTFRAME
#define ELYSIUM_GRAPHICS_INPUT_INPUTFRAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Input
{
	class ELYSIUM_GRAPHICS_API InputFrame final
	{
	public:
		InputFrame();
		InputFrame(const InputFrame& Source) = delete;
		InputFrame(InputFrame&& Right) noexcept = delete;
		~InputFrame();

		InputFrame& operator=(const InputFrame& Source) = delete;
		InputFrame& operator=(InputFrame&& Right) noexcept = delete;
	private:
	};
}
#endif
