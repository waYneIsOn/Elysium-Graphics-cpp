/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_FENCEDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_FENCEDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFENCE
#include "../Elysium.Graphics/INativeFence.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#include "IncludeDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_LOGICALDEVICEDX12
#include "LogicalDeviceDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API FenceDX12 final : public INativeFence
	{
	public:
		FenceDX12(const LogicalDeviceDX12 & LogicalDevice, const bool SetSignaled = false);
		FenceDX12(const FenceDX12& Source) = delete;
		FenceDX12(FenceDX12&& Right) noexcept = delete;
		virtual ~FenceDX12();

		FenceDX12& operator=(const FenceDX12& Source) = delete;
		FenceDX12& operator=(FenceDX12&& Right) noexcept = delete;

		virtual void Wait(const Elysium::Core::uint64_t Timeout) const override;
		virtual void Reset() override;
	private:
		const LogicalDeviceDX12& _LogicalDevice;
		ID3D12Fence* _NativeFence;
	};
}
#endif
