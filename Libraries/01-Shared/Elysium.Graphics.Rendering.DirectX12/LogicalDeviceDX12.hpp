/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_LOGICALDEVICEDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_LOGICALDEVICEDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVELOGICALDEVICE
#include "../Elysium.Graphics/INativeLogicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#include "IncludeDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PRESENTATIONPARAMETERSDX12
#include "PresentationParametersDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class FenceDX12;
	class PhysicalDeviceDX12;
	class QueueDX12;
	class SwapchainDX12;

	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API LogicalDeviceDX12 final : public INativeLogicalDevice
	{
		friend class FenceDX12;
		friend class PhysicalDeviceDX12;
		friend class QueueDX12;
		friend class SwapchainDX12;
	public:
		LogicalDeviceDX12(const PhysicalDeviceDX12& PhysicalDevice, PresentationParametersDX12& PresentationParameters);
		LogicalDeviceDX12(const LogicalDeviceDX12& Source) = delete;
		LogicalDeviceDX12(LogicalDeviceDX12&& Right) noexcept = delete;
		virtual ~LogicalDeviceDX12();

		LogicalDeviceDX12& operator=(const LogicalDeviceDX12& Source) = delete;
		LogicalDeviceDX12& operator=(LogicalDeviceDX12&& Right) noexcept = delete;

		virtual const INativePhysicalDevice& GetPhysicalDevice() const override;

		virtual PresentationParametersDX12& GetPresentationParameters() const override;

		virtual void Wait() const override;
	private:
		const PhysicalDeviceDX12& _PhysicalDevice;
		PresentationParametersDX12& _PresentationParameters;

		IDXGIFactory2* _Factory;
		ID3D12Device6* _NativeDevice;
	};
}
#endif
