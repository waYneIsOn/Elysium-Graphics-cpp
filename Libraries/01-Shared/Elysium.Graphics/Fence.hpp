/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_FENCE
#define ELYSIUM_GRAPHICS_RENDERING_FENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFENCE
#include "INativeFence.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;
	class Queue;

	class ELYSIUM_GRAPHICS_API Fence final
	{
		friend class GraphicsDevice;
		friend class Queue;
	public:
		Fence(const Fence& Source) = delete;
		Fence(Fence&& Right) noexcept = delete;
		~Fence();

		Fence& operator=(const Fence& Source) = delete;
		Fence& operator=(Fence&& Right) noexcept = delete;

		void Wait(const Elysium::Core::uint64_t Timeout) const;
		void Reset();
	private:
		Fence(INativeFence& NativeFence);

		INativeFence& _NativeFence;
	};
}
#endif
