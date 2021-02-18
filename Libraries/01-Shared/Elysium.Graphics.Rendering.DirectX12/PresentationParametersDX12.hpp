/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PRESENTATIONPARAMETERSDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PRESENTATIONPARAMETERSDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#include "../Elysium.Graphics/PresentationParameters.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_DEVICEQUEUECREATEINFODX12
#include "DeviceQueueCreateInfoDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class PhysicalDeviceDX12;
	class QueueDX12;

	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API PresentationParametersDX12 final : public Elysium::Graphics::PresentationParameters
	{
		friend class PhysicalDeviceDX12;
		friend class QueueDX12;
	public:
		PresentationParametersDX12();
		PresentationParametersDX12(const PresentationParametersDX12& Source) = delete;
		PresentationParametersDX12(PresentationParametersDX12&& Right) noexcept = delete;
		virtual ~PresentationParametersDX12();

		PresentationParametersDX12& operator=(const PresentationParametersDX12& Source) = delete;
		PresentationParametersDX12& operator=(PresentationParametersDX12&& Right) noexcept = delete;

		virtual void SetExtent(const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height) override;

		void AddDeviceQueueCreateInfo(DeviceQueueCreateInfoDX12&& CreateInfo);
		void ClearDeviceQueueCreateInfo();
	private:
		// information required for creation queues
		Core::Collections::Template::List<DeviceQueueCreateInfoDX12> _DeviceQueueCreateInfos = Core::Collections::Template::List<DeviceQueueCreateInfoDX12>(0);
	};
}
#endif
