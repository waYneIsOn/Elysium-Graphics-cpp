/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_COMMANDPOOL
#define ELYSIUM_GRAPHICS_RENDERING_COMMANDPOOL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_COMMANDBUFFER
#include "CommandBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDPOOL
#include "INativeCommandPool.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class Queue;

	class ELYSIUM_GRAPHICS_API CommandPool final
	{
		friend class Queue;
	public:
		CommandPool(const CommandPool& Source) = delete;
		CommandPool(CommandPool&& Right) noexcept = delete;
		~CommandPool();

		CommandPool& operator=(const CommandPool& Source) = delete;
		CommandPool& operator=(CommandPool&& Right) noexcept = delete;

		CommandBuffer CreateCommandBuffer(const bool IsPrimary);

		void Reset();
	private:
		CommandPool(Native::INativeCommandPool* NativeCommandPool);

		Native::INativeCommandPool* _NativeCommandPool;
	};
}
#endif
