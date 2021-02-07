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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
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

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_QUEUEDX12
#include "QueueDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_SWAPCHAINDX12
#include "SwapchainDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class PhysicalDeviceDX12;

	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API LogicalDeviceDX12 final : public INativeLogicalDevice
	{
		friend class PhysicalDeviceDX12;
	public:
		LogicalDeviceDX12(const LogicalDeviceDX12& Source) = delete;
		LogicalDeviceDX12(LogicalDeviceDX12&& Right) noexcept = delete;
		virtual ~LogicalDeviceDX12();

		LogicalDeviceDX12& operator=(const LogicalDeviceDX12& Source) = delete;
		LogicalDeviceDX12& operator=(LogicalDeviceDX12&& Right) noexcept = delete;

		SwapchainDX12 CreateSwapchain(const PresentationParametersDX12& PresentationParameter);

		virtual QueueDX12& RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index) override;
	private:
		LogicalDeviceDX12(IDXGIFactory2* Factory, ID3D12Device6* Device, Elysium::Core::Collections::Template::Array<QueueDX12>&& Queues);

		IDXGIFactory2* _Factory;
		ID3D12Device6* _Device;
		Core::Collections::Template::Array<QueueDX12> _Queues;
	};
}
#endif
