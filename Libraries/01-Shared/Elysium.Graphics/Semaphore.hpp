/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_SEMAPHORE
#define ELYSIUM_GRAPHICS_RENDERING_SEMAPHORE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESEMAPHORE
#include "INativeSemaphore.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API Semaphore final
	{
		friend class GraphicsDevice;
		friend class Queue;
	public:
		Semaphore(const Semaphore& Source) = delete;
		Semaphore(Semaphore&& Right) noexcept = delete;
		~Semaphore();

		Semaphore& operator=(const Semaphore& Source) = delete;
		Semaphore& operator=(Semaphore&& Right) noexcept = delete;

		void Wait(const Elysium::Core::uint64_t Timeout);
	private:
		Semaphore(Native::INativeSemaphore& NativeSemaphore);

		Native::INativeSemaphore& _NativeSemaphore;
	};
}
#endif
