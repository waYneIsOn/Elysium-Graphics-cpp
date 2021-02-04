/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUECAPABILITIESVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUECAPABILITIESVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class QueueCapabilitiesVk : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class QueueCapabilitiesVk
#else
#error "undefined os"
#endif
	{
		None = 0x00000000,
		Graphics = 0x00000001,
		Compute = 0x00000002,
		Transfer = 0x00000004,
		SparseBinding = 0x00000008,

		//Protected = 0x00000010,
	};

	inline QueueCapabilitiesVk operator|(const QueueCapabilitiesVk Left, const QueueCapabilitiesVk Right)
	{
		return static_cast<QueueCapabilitiesVk>(static_cast<Elysium::Core::uint32_t>(Left) | static_cast<Elysium::Core::uint32_t>(Right));
	}
	inline QueueCapabilitiesVk operator&(const QueueCapabilitiesVk Left, const QueueCapabilitiesVk Right)
	{
		return static_cast<QueueCapabilitiesVk>(static_cast<Elysium::Core::uint32_t>(Left) & static_cast<Elysium::Core::uint32_t>(Right));
	}
}
#endif
