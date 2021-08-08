/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_QUEUE
#define ELYSIUM_GRAPHICS_RENDERING_QUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_COMMANDPOOL
#include "CommandPool.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_FENCE
#include "Fence.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SEMAPHORE
#include "Semaphore.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEQUEUE
#include "INativeQueue.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;

	class ELYSIUM_GRAPHICS_API Queue final
	{
		friend class GraphicsDevice;
	public:
		Queue(const Queue& Source) = delete;
		Queue(Queue&& Right) noexcept = delete;
		~Queue();

		Queue& operator=(const Queue& Source) = delete;
		Queue& operator=(Queue&& Right) noexcept = delete;

		CommandPool CreateCommandPool();

		void Submit(const CommandBuffer& CommmandBuffer, const Semaphore& PresentSemaphore, const Semaphore& RenderSemaphore, const Fence& Fence);
		void Wait() const;
	private:
		Queue(Native::INativeQueue& NativeQueue);

		Native::INativeQueue& _NativeQueue;
	};
}
#endif
