/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#define ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_FENCE
#include "Fence.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_FRAMEBUFFER
#include "Framebuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_QUEUE
#include "Queue.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_RENDERPASS
#include "RenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SEMAPHORE
#include "Semaphore.hpp"
#endif

namespace Elysium::Graphics
{
	class PresentationParameters;
}

namespace Elysium::Graphics::Rendering
{
	namespace Native
	{
		class INativeGraphicsDevice;
	}

	class ELYSIUM_GRAPHICS_API GraphicsDevice final
	{
		friend class CommandBuffer;
		friend class GraphicsPipeline;
		friend class Pipeline;
		friend class ShaderModule;
	public:
		GraphicsDevice(Native::INativeGraphicsDevice& NativeGraphicsDevice);
		GraphicsDevice(const GraphicsDevice& Source) = delete;
		GraphicsDevice(GraphicsDevice&& Right) noexcept = delete;
		~GraphicsDevice();

		GraphicsDevice& operator=(const GraphicsDevice& Source) = delete;
		GraphicsDevice& operator=(GraphicsDevice&& Right) noexcept = delete;

		PresentationParameters& GetPresentationParameters();

		const RenderPass& GetDefaultRenderPass() const;
		const FrameBuffer& GetFrameBuffer() const;

		const Fence& GetRenderFence() const;
		const Semaphore& GetPresentationSemaphore() const;
		const Semaphore& GetRenderSemaphore() const;

		Queue& GetGraphicsQueue();

		void Wait() const;
		const bool BeginDraw();
		void EndDraw();
	private:
		Native::INativeGraphicsDevice& _NativeGraphicsDevice;

		RenderPass _DefaultRenderPass;
		FrameBuffer _FrameBuffer;
		Fence _RenderFence;
		Semaphore _PresentationSemaphore;
		Semaphore _RenderSemaphore;
		Queue _GraphicsQueue;
	};
}
#endif
