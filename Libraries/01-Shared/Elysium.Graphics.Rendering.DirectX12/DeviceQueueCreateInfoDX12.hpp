/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_DEVICEQUEUECREATEINFODX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_DEVICEQUEUECREATEINFODX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUEFLAGSDX12
#include "CommandQueueFlagsDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUEPRIORITYDX12
#include "CommandQueuePriorityDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUETYPEDX12
#include "CommandQueueTypeDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API DeviceQueueCreateInfoDX12 final
	{
	public:
		DeviceQueueCreateInfoDX12();
		DeviceQueueCreateInfoDX12(const DeviceQueueCreateInfoDX12& Source);
		DeviceQueueCreateInfoDX12(DeviceQueueCreateInfoDX12&& Right) noexcept;
		~DeviceQueueCreateInfoDX12();

		DeviceQueueCreateInfoDX12& operator=(const DeviceQueueCreateInfoDX12& Source);
		DeviceQueueCreateInfoDX12& operator=(DeviceQueueCreateInfoDX12&& Right) noexcept;

		const Elysium::Core::uint32_t& GetNodeMask() const;
		const CommandQueueFlagsDX12& GetFlags() const;
		const CommandQueuePriorityDX12& GetPriority() const;
		const CommandQueueTypeDX12& GetType() const;

		void SetNodeMask(const Elysium::Core::uint32_t Value);
		void SetFlags(const CommandQueueFlagsDX12 Value);
		void SetPriority(const CommandQueuePriorityDX12 Value);
		void SetType(const CommandQueueTypeDX12 Value);
	private:
		Elysium::Core::uint32_t _NodeMask;
		CommandQueuePriorityDX12 _Priority;
		CommandQueueFlagsDX12 _Flags;
		CommandQueueTypeDX12 _Type;
	};
}
#endif
