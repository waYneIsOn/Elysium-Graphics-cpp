/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSDEVICE
#include "../Elysium.Graphics/INativeGraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEPTHBUFFERVK
#include "DepthBufferVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FENCEVK
#include "FenceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSINSTANCEVK
#include "GraphicsInstanceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#include "PresentationParametersVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEVK
#include "QueueVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK
#include "SemaphoreVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINVK
#include "SwapchainVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class CommandBufferVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API GraphicsDeviceVk final : public INativeGraphicsDevice
	{
		friend class CommandBufferVk;
	public:
		GraphicsDeviceVk(GraphicsInstanceVk& GraphicsInstance, PresentationParametersVk& PresentationParameters);
		GraphicsDeviceVk(const GraphicsDeviceVk& Source) = delete;
		GraphicsDeviceVk(GraphicsDeviceVk&& Right) noexcept = delete;
		~GraphicsDeviceVk();

		GraphicsDeviceVk& operator=(const GraphicsDeviceVk& Source) = delete;
		GraphicsDeviceVk& operator=(GraphicsDeviceVk&& Right) noexcept = delete;

		virtual const GraphicsInstanceVk& GetGraphicsAPI() const override;
		virtual PresentationParametersVk& GetPresentationParameters() override;
		virtual const PhysicalDeviceVk& GetPhysicalDevice() const override;

		virtual const FenceVk& GetRenderFence() const override;
		virtual const SemaphoreVk& GetPresentationSemaphore() const override;
		virtual const SemaphoreVk& GetRenderSemaphore() const override;

		virtual QueueVk& GetGraphicsQueue() override;

		virtual void Wait() const override;
		virtual const bool BeginDraw() override;
		virtual void EndDraw() override;
	private:
		GraphicsInstanceVk& _GraphicsInstance;
		PresentationParametersVk& _PresentationParameters;

		SurfaceVk _Surface;
		LogicalDeviceVk _LogicalDevice;
		QueueVk _GraphicsQueue;
		QueueVk _PresentationQueue;
		SwapchainVk _Swapchain;
		DepthBufferVk _DepthBuffer;
		FenceVk _RenderFence;
		SemaphoreVk _PresentationSemaphore;
		SemaphoreVk _RenderSemaphore;
	};
}
#endif
