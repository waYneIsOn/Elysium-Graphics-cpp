/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESEMAPHORE
#include "../Elysium.Graphics/INativeSemaphore.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SemaphoreVk final : public Native::INativeSemaphore
	{
		friend class GraphicsDeviceVk;
		friend class QueueVk;
	public:
		SemaphoreVk(const GraphicsDeviceVk& GraphicsDevice);
		SemaphoreVk(const SemaphoreVk& Source) = delete;
		SemaphoreVk(SemaphoreVk&& Right) noexcept = delete;
		virtual ~SemaphoreVk();

		SemaphoreVk& operator=(const SemaphoreVk& Source) = delete;
		SemaphoreVk& operator=(SemaphoreVk&& Right) noexcept = delete;

		virtual void Wait(const Elysium::Core::uint64_t Timeout) override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		VkSemaphore _NativeSemaphoreHandle;

		VkSemaphore CreateNativeSemaphore();

		void DestroyNativeSemaphore();
	};
}
#endif
